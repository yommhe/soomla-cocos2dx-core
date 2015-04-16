(function () {

  if (_.isUndefined(window.Soomla)) {
    window.Soomla = {};
  }

  var PrevSoomla = window.Soomla;

  var Soomla = _.extend(PrevSoomla, {Models: {}}); // merge with binding instance

  Soomla.platform = {
    name: cc.sys.os.toLowerCase(),
    isNativeSupported: function isNativeSupported() {
      return this.isAndroid() || this.isIos();
    },
    isAndroid: function isAndroid() {
      return this.name === 'android';
    },
    isIos: function isIos() {
      return this.name === 'ios';
    }
  };

  Soomla.DEBUG = false;

  Soomla.factory = {
    classFactories: {},
    create: function (data) {
      data.className = data.className ||
      (data.purchaseType === 'market' && 'PurchaseWithMarket') ||
      (data.purchaseType === 'virtualItem' && 'PurchaseWithVirtualItem');
      this.checkForClass(data);
      var classFactory = this.classFactories[data.className];
      if (classFactory) {
        var result = classFactory.call(this, data);
        result.factored = true;
        return result;
      } else {
        Soomla.logError('Cannot find factory for className: ' + data.className);
        return null;
      }
    },
    checkForClass: function (data) {
      _.forEach(data, function (value, key) {
        if (_.isPlainObject(value)) {
          value.className = value.className ||
          (value.purchaseType === 'market' && 'PurchaseWithMarket') ||
          (value.purchaseType === 'virtualItem' && 'PurchaseWithVirtualItem');

          if (!value.className) {
            this.checkForClass(value);
          } else {
            data[key] = this.create(value);
          }
        }
      }, this);
    }
  };

  var declareClass = Soomla.declareClass = function (className, extension, parentClass) {

    extension = extension || {};

    var fields = _.omit(extension, _.functions(extension));
    var methods = _.pick(extension, _.functions(extension));

    var Clazz = function () {

      _.extend(this, fields, {
        className: className
      });

      if (_.isFunction(this.ctor)) {
        this.ctor.call(this);
      }

      return this;
    };

    Clazz.name = className;


    if (parentClass) {
      Clazz.prototype = new parentClass();
      Clazz.prototype.constructor = Clazz;
      Clazz.prototype.__super__ = parentClass.prototype;
    }
    _.extend(Clazz.prototype, methods);


    Clazz.create = function (values) {
      var instance = new Clazz();

      _.assign(instance, values ? _.omit(values, ['className', '__super__']) : {});

      if (_.isFunction(instance.onCreate)) {
        instance.onCreate.call(instance);
      }
      return instance;
    };

    Soomla.factory.classFactories[className] = Clazz.create;

    return Clazz;
  };

  /**
   * Domain
   */
  var Domain = Soomla.Models.Domain = declareClass('Domain', {});

  /**
   * SoomlaEntity
   */
  var SoomlaEntity = Soomla.Models.SoomlaEntity = declareClass('SoomlaEntity', {
    name: '',
    description: '',
    itemId: null,
    equals: function equals(obj) {
      // If parameter is null return false.
      if (obj == null) {
        return false;
      }

      if (obj.className != this.className) {
        return false;
      }

      if (obj.itemId != this.itemId) {
        return false;
      }

      return true;
    }
  }, Domain);


  /**
   * Recurrence
   */
  var Recurrence = Soomla.Models.Recurrence = {
    EVERY_MONTH: 0,
    EVERY_WEEK: 1,
    EVERY_DAY: 2,
    EVERY_HOUR: 3,
    NONE: 4
  };

  /**
   * CoreConsts
   */
  var CoreConsts = Soomla.Models.CoreConsts = {
    EVENT_REWARD_GIVEN: 'com.soomla.events.RewardGivenEvent',
    EVENT_REWARD_TAKEN: 'com.soomla.events.RewardTakenEvent',
    EVENT_CUSTOM: 'com.soomla.events.CustomEvent'
  };

  /**
   * DateTimeRange
   */
  var DateTimeRange = Soomla.Models.DateTimeRange = declareClass('DateTimeRange', {
    schedTimeRangeStart: null,
    schedTimeRangeEnd: null
  });

  /**
   * Schedule
   */
  var Schedule = Soomla.Models.Schedule = declareClass('Schedule', {
    schedRecurrence: null,
    schedTimeRanges: null,
    schedApprovals: null,
    approve: function approve(activationTimes) {
      var now = Date.now();

      if (this.schedApprovals && this.schedApprovals < 1 && (!this.schedTimeRanges || this.schedTimeRanges.length == 0)) {
        Soomla.logDebug('There\'s no activation limit and no TimeRanges. APPROVED!');
        return true;
      }

      if (this.schedApprovals && this.schedApprovals > 0 && activationTimes >= this.schedApprovals) {
        Soomla.logDebug('Activation limit exceeded.');
        return false;
      }

      if ((!this.schedTimeRanges || this.schedTimeRanges.length == 0)) {
        Soomla.logDebug('We have an activation limit that was not reached. Also, we don\'t have any time ranges. APPROVED!');
        return true;
      }


      // NOTE: From this point on ... we know that we didn't reach the activation limit AND we have TimeRanges.
      //		 We'll just make sure the time ranges and the Recurrence copmlies.

      var found = _.find(this.schedTimeRanges, function (dateTimeRange) {
        if (now < dateTimeRange.schedTimeRangeStart && now > dateTimeRange.schedTimeRangeEnd) {
          Soomla.logDebug('We are just in one of the time spans, it can\'t get any better then that. APPROVED!');
          return true;
        }
      });

      if (found) {
        return true;
      }

      // we don't need to continue if RequiredRecurrence is NONE
      if (this.schedRecurrence == Recurrence.NONE) {
        return false;
      }

      var _this = this;
      return _.find(this.schedTimeRanges, function (dateTimeRange) {
          if (now.getMinutes() >= dateTimeRange.schedTimeRangeStart.getMinutes()
            && now.getMinutes() <= dateTimeRange.schedTimeRangeEnd.getMinutes()) {

            Soomla.logDebug('Now is in one of the time ranges\' minutes span.');

            if (_this.schedRecurrence == Recurrence.EVERY_HOUR) {
              Soomla.logDebug('It\'s a EVERY_HOUR recurrence. APPROVED!');
              return true;
            }

            if (now.getHours() >= dateTimeRange.schedTimeRangeStart.getHours()
              && now.getHours() <= dateTimeRange.schedTimeRangeEnd.getHours()) {

              Soomla.logDebug('Now is in one of the time ranges\' hours span.');

              if (_this.schedRecurrence == Recurrence.EVERY_DAY) {
                Soomla.logDebug('It\'s a EVERY_DAY recurrence. APPROVED!');
                return true;
              }

              if (now.getDay() >= dateTimeRange.schedTimeRangeStart.getDay()
                && now.getDay() <= dateTimeRange.schedTimeRangeEnd.getDay()) {

                Soomla.logDebug('Now is in one of the time ranges\' day-of-week span.');

                if (_this.schedRecurrence == Recurrence.EVERY_WEEK) {
                  Soomla.logDebug('It\'s a EVERY_WEEK recurrence. APPROVED!');
                  return true;
                }

                if (now.getDate() >= dateTimeRange.schedTimeRangeStart.getDate()
                  && now.getDate() <= dateTimeRange.schedTimeRangeEnd.getDate()) {

                  Soomla.logDebug('Now is in one of the time ranges\' days span.');

                  if (_this.schedRecurrence == Recurrence.EVERY_MONTH) {
                    Soomla.logDebug('It\'s a EVERY_MONTH recurrence. APPROVED!');
                    return true;
                  }
                }
              }
            }
          }
        }) || false;
    }
  });

  Schedule.createAnyTimeOnce = function createAnyTimeOnce() {
    return Schedule.create({
      schedRecurrence: Recurrence.NONE,
      schedApprovals: 1
    });
  };
  Schedule.createAnyTimeLimited = function createAnyTimeLimited(activationLimit) {
    return Schedule.create({
      schedRecurrence: Recurrence.NONE,
      schedApprovals: activationLimit
    });
  };
  Schedule.createAnyTimeUnLimited = function createAnyTimeUnLimited() {
    return Schedule.create({
      schedRecurrence: Recurrence.NONE,
      schedApprovals: 0
    });
  };

  //noinspection JSUnusedGlobalSymbols
  /**
   * Reward
   */
  var Reward = Soomla.Models.Reward = declareClass("Reward", {
    schedule: null,
    take: function take() {
      if (!Soomla.rewardStorage.isRewardGiven(this)) {
        Soomla.logDebug("Reward not given. id: " + id);
        return false;
      }

      if (this.takeInner()) {
        Soomla.rewardStorage.setRewardStatus(this, false);
        return true;
      }

      return false;
    },
    give: function give() {
      if (!this.schedule.approve(Soomla.rewardStorage.getTimesGiven(this))) {
        Soomla.logDebug("(Give) Reward is not approved by Schedule. id: " + this.itemId);
        return false;
      }

      if (this.giveInner()) {
        Soomla.rewardStorage.setRewardStatus(this, true);
        return true;
      }

      return false;
    },
    isOwned: function isOwned() {
      return Soomla.rewardStorage.isRewardGiven(this);
    },
    takeInner: function takeInner() {
      return new Error("takeInner is not implemented");
    },
    giveInner: function giveInner() {
      return new Error("giveInner is not implemented");
    },
    onCreate: function () {
      Reward.addReward(this);
    }
  }, SoomlaEntity);

  Reward.rewardsMap = {};

  Reward.getReward = function (id) {
    if (id in Soomla.Models.Reward.rewardsMap) {
      return Soomla.Models.Reward.rewardsMap[id];
    }

    return null;
  };

  Reward.addReward = function (reward) {
    Soomla.Models.Reward.rewardsMap[reward.itemId] = reward;
  };

  /**
   * AggregateReward
   */
  var AggregateReward = Soomla.Models.AggregateReward = declareClass("AggregateReward", {
    rewards: null
  }, Reward);

  /**
   * BadgeReward
   */
  var BadgeReward = Soomla.Models.BadgeReward = declareClass("BadgeReward", {
    iconUrl: null,
    takeInner: function takeInner() {
      // nothing to do here... the parent Reward takes in storage
      return true;
    },
    giveInner: function giveInner() {
      // nothing to do here... the parent Reward gives in storage
      return true;
    }
  }, Reward);

  /**
   * RandomReward
   */
  var RandomReward = Soomla.Models.RandomReward = declareClass("RandomReward", {
    lastGivenReward: null,
    takeInner: function takeInner() {
      // for now is able to take only last given
      if (this.lastGivenReward == null) {
        return false;
      }

      var taken = this.lastGivenReward.take();
      this.lastGivenReward = null;

      return taken;
    },
    giveInner: function giveInner() {
      var randomReward = _.sample(this.rewards);
      randomReward.give();
      this.lastGivenReward = randomReward;

      return true;
    }
  }, AggregateReward);

  /**
   * SequenceReward
   */
  var SequenceReward = Soomla.Models.SequenceReward = declareClass("SequenceReward", {
    takeInner: function takeInner() {
      var idx = Soomla.rewardStorage.getLastSeqIdxGiven(this);
      if (idx <= 0) {
        return false; // all rewards in the sequence were taken
      }
      Soomla.rewardStorage.setLastSeqIdxGiven(this, --idx);
      return true;
    },
    giveInner: function giveInner() {
      var idx = Soomla.rewardStorage.getLastSeqIdxGiven(this);
      if (idx >= this.rewards.length) {
        return false; // all rewards in the sequence were given
      }
      Soomla.rewardStorage.setLastSeqIdxGiven(this, ++idx);
      return true;
    },
    getLastGivenReward: function getLastGivenReward() {
      var idx = Soomla.rewardStorage.getLastSeqIdxGiven(this);
      if (idx < 0) {
        return null;
      }
      return this.rewards[idx];
    },
    hasMoreToGive: function hasMoreToGive() {
      return Soomla.rewardStorage.getLastSeqIdxGiven(this) < this.rewards.length;
    },
    forceNextRewardToGive: function forceNextRewardToGive(reward) {
      for (var i = 0; i < this.rewards.length; i++) {
        if (reward.equals(this.reward[i])) {
          Soomla.rewardStorage.setLastSeqIdxGiven(this, i - 1);
          return true;
        }
      }
      return false;
    }
  }, AggregateReward);


  /**
   * Soomla
   */
  Soomla.DB_KEY_PRFIX = 'soomla.';
  Soomla.initialize = function initialize(soomlaSecret) {
    if (!soomlaSecret || soomlaSecret.length == 0) {
      Soomla.logError("Can't initialize SOOMLA without soomlaSecret");
      return false;
    }

    Soomla.CoreEventDispatcher.initShared();
    Soomla.coreBridge = Soomla.platform.isNativeSupported() ? NativeCoreBridge.create() : BridgelessCoreBridge.create();

    Soomla.callNative({
      method: "CCSoomla::initialize",
      soomlaSecret: soomlaSecret
    });

    return true;
  };

  /**
   * NativeCoreBridge
   */
  var NativeCoreBridge = Soomla.NativeCoreBridge = declareClass("NativeCoreBridge", {
    ctor: function () {
      this.bindNative();
    },
    bindNative: function () {
      Soomla.logDebug('Binding to native platform bridge...');
      if (Soomla.platform.isAndroid()) {
        jsb.reflection.callStaticMethod('com/soomla/cocos2dx/common/CoreBridgeBinder', "bind", "()V");
      } else if (Soomla.platform.isIos()) {
        jsb.reflection.callStaticMethod('CoreBridge', 'initShared');
      } else {
        Soomla.logError('Unsupported platform: ' + Soomla.platform.name);
      }
    }
  });

  /**
   * BridgelessCoreBridge
   */
  var BridgelessCoreBridge = Soomla.BridgelessCoreBridge = declareClass("BridgelessCoreBridge", {});


  /**
   * NativeKeyValueStorage
   */
  var NativeKeyValueStorage = Soomla.NativeKeyValueStorage = declareClass("NativeKeyValueStorage", {
    getValue: function getValue(key) {
      var result = Soomla.callNative({
        method: "CCNativeKeyValueStorage::getValue",
        key: key
      });
      return result['return'];
    },
    setValue: function setValue(key, val) {
      Soomla.callNative({
        method: "CCNativeKeyValueStorage::setValue",
        key: key,
        val: val
      });
    },
    deleteKeyValue: function deleteKeyValue(key) {
      Soomla.callNative({
        method: "CCNativeKeyValueStorage::deleteKeyValue",
        key: key
      });
    },
    purge: function purge() {
      Soomla.callNative({
        method: "CCNativeKeyValueStorage::purge"
      });
    }
  });

  /**
   * BridgelessKeyValueStorage
   */
  var BridgelessKeyValueStorage = Soomla.BridgelessKeyValueStorage = declareClass("BridgelessKeyValueStorage", {
    KEY_VALUE_STORAGE_KEY: 'soomla.kvs.keys',
    mStoredKeys: [],

    ctor: function () {
      this.loadStoredKeys();
    },

    getValue: function getValue(key) {
      var defaultValue = "";
      var result = cc.sys.localStorage.getItem(key) || defaultValue;
      Soomla.logDebug('getValue with key: ' + key + ', result: ' + result);
      return result;
    },
    setValue: function setValue(key, val) {
      cc.sys.localStorage.setItem(key, val);

      Soomla.logDebug('setValue with key: ' + key + ', value: ' + val);

      this.addStoredKeys(key);
      this.saveStoredKeys();
    },
    deleteKeyValue: function deleteKeyValue(key) {
      cc.sys.localStorage.removeItem(key);

      Soomla.logDebug('deleteKeyValue with key: ' + key);

      this.removeStoredKeys(key);
      this.saveStoredKeys();
    },
    purge: function purge() {
      Soomla.logDebug('purge');

      _.forEach(this.mStoredKeys, function (key) {
        this.deleteKeyValue(key);
      }, this);

      cc.sys.localStorage.setItem(this.KEY_VALUE_STORAGE_KEY, "");
    },

    addStoredKeys: function (key) {
      if (this.mStoredKeys.indexOf(key) < 0) {
        this.mStoredKeys.push(key);
      }
    },
    removeStoredKeys: function (key) {
      var idx = this.mStoredKeys.indexOf(key);
      if (idx >= 0) {
        this.mStoredKeys.splice(idx, 1);
      }
    },
    saveStoredKeys: function () {
      cc.sys.localStorage.setItem(this.KEY_VALUE_STORAGE_KEY, JSON.stringify(this.mStoredKeys));
    },
    loadStoredKeys: function () {
      var strKeys = cc.sys.localStorage.getItem(this.KEY_VALUE_STORAGE_KEY);
      if (strKeys) {
        this.mStoredKeys = JSON.parse(strKeys);
      }
    }
  });

  Soomla.keyValueStorage = Soomla.platform.isNativeSupported() ? NativeKeyValueStorage.create() : BridgelessKeyValueStorage.create();

  /**
   * NativeRewardStorage
   */
  var NativeRewardStorage = Soomla.NativeRewardStorage = declareClass("NativeRewardStorage", {
    setRewardStatus: function setRewardStatus(reward, give, notify) {
      notify = notify || _.isUndefined(notify);
      Soomla.callNative({
        method: "CCNativeRewardStorage::setRewardStatus",
        reward: reward.itemId,
        give: give,
        notify: notify
      });
    },
    getTimesGiven: function getTimesGiven(reward) {
      var result = Soomla.callNative({
        method: "CCNativeRewardStorage::getTimesGiven",
        reward: reward.itemId
      });
      return result['return'];
    },
    isRewardGiven: function isRewardGiven(reward) {
      return this.getTimesGiven(reward) > 0;
    },
    getLastSeqIdxGiven: function getLastSeqIdxGiven(sequenceReward) {
      var result = Soomla.callNative({
        method: "CCNativeRewardStorage::getLastSeqIdxGiven",
        reward: sequenceReward.itemId
      });
      return result['return'];
    },
    setLastSeqIdxGiven: function setLastSeqIdxGiven(sequenceReward, idx) {
      Soomla.callNative({
        method: "CCNativeRewardStorage::setLastSeqIdxGiven",
        reward: sequenceReward.itemId,
        idx: idx
      });
    }
  });

  /**
   * BridgelessRewardStorage
   */
  var BridgelessRewardStorage = Soomla.BridgelessRewardStorage = declareClass("BridgelessRewardStorage", {
    setRewardStatus: function setRewardStatus(reward, give, notify) {
      notify = notify || _.isUndefined(notify);
      this.setTimesGiven(reward, give, notify);
    },
    getTimesGiven: function getTimesGiven(reward) {
      var key = this.keyRewardTimesGiven(reward.getId());
      var val = Soomla.keyValueStorage.getValue(key);
      return (!_.isUndefined(val) && !_.isNull(val)) ? val : 0;
    },
    isRewardGiven: function isRewardGiven(reward) {
      return this.getTimesGiven(reward) > 0;
    },
    getLastSeqIdxGiven: function getLastSeqIdxGiven(sequenceReward) {
      var key = this.keyRewardIdxSeqGiven(sequenceReward.getId());
      var val = Soomla.keyValueStorage.getValue(key);
      return (!_.isUndefined(val) && !_.isNull(val)) ? val : -1;
    },
    setLastSeqIdxGiven: function setLastSeqIdxGiven(sequenceReward, idx) {
      var key = this.keyRewardIdxSeqGiven(sequenceReward.getId());
      Soomla.keyValueStorage.setValue(key, idx);
    },


    setTimesGiven: function setTimesGiven(reward, up, notify) {
      notify = notify || _.isUndefined(notify);
      var total = this.getTimesGiven(reward) + (up ? 1 : -1);
      if (total < 0) {
        total = 0;
      }

      var key = this.keyRewardTimesGiven(reward.getId());
      Soomla.keyValueStorage.setValue(key, total);

      if (up) {
        key = this.keyRewardLastGiven(reward.getId());
        Soomla.keyValueStorage.setValue(key, Date.now());
      }

      if (notify) {
        if (up) {
          Soomla.fireSoomlaEvent(CoreConsts.EVENT_REWARD_GIVEN, [reward]);
        } else {
          Soomla.fireSoomlaEvent(CoreConsts.EVENT_REWARD_TAKEN, [reward]);
        }
      }
    },
    keyRewards: function keyRewards(rewardId, postfix) {
      return Soomla.DB_KEY_PRFIX + 'rewards.' + rewardId + '.' + postfix;
    },
    keyRewardIdxSeqGiven: function keyRewardIdxSeqGiven(rewardId) {
      return this.keyRewards(rewardId, "seq.id");
    },
    keyRewardTimesGiven: function keyRewardTimesGiven(rewardId) {
      return this.keyRewards(rewardId, "timesGiven");
    },
    keyRewardLastGiven: function keyRewardLastGiven(rewardId) {
      return this.keyRewards(rewardId, "lastGiven");
    }
  });

  Soomla.rewardStorage = Soomla.platform.isNativeSupported() ? NativeRewardStorage.create() : BridgelessRewardStorage.create();

  /**
   * CoreEventHandler
   * Here for documentation reasons only, shows signatures for event handlers
   */
  var CoreEventHandler = Soomla.CoreEventHandler = function () {
    return Soomla.declareClass("CoreEventHandler", {
      onRewardGivenEvent: function (reward) {
      },
      onRewardTakenEvent: function (reward) {
      },
      onCustomEvent: function (name, extra) {
      }
    });
  }();

  /**
   * Root definitions
   */

  var SoomlaEventDispatcher = Soomla.SoomlaEventDispatcher = function () {
    return Soomla.declareClass('SoomlaEventDispatcher', {
      eventHandlers: {},
      ndkCallback: function ndkCallback(parameters) {

        var eventName = parameters.method;
        if (!eventName) {
          // Suppress any events without callbacks (push event probably)
          return;
        }

        var handler = this.eventHandlers[eventName];

        if (handler) {
          handler(parameters);
        } else {
          Soomla.logDebug('Unregistered event happened: ' + eventName);
        }
      },
      registerEventHandler: function registerEventHandler(key, handler) {
        this.eventHandlers[key] = handler;
      },
      unregisterEventHandler: function (key) {
        delete this.eventHandlers[key];
      }
    });
  }();

  Soomla.soomlaEventDispatcher = new SoomlaEventDispatcher();

  Soomla.eventHandlers = {};

  Soomla.addEventHandler = Soomla.on = function (eventName, handler, target) {
    var handlersArray = Soomla.eventHandlers[eventName];
    if (handlersArray === undefined) {
      handlersArray = Soomla.eventHandlers[eventName] = [];
    }

    var foundHandler = _.find(handlersArray, function (callbackObject) {
      return ((callbackObject.obj == target) && (callbackObject.callback == handler));
    });

    if (foundHandler != null) {
      return;
    }

    handlersArray.push({
      obj: target,
      callback: handler
    });
  };

  Soomla.removeEventHandler = Soomla.off = function (eventName, handler) {
    var handlersArray = Soomla.eventHandlers[eventName];
    if (handlersArray === undefined) {
      return;
    }

    var filteredArray = _.filter(handlersArray, function (callbackObject) {
      return (callbackObject.callback != handler);
    });
    Soomla.eventHandlers[eventName] = filteredArray;
  };

  Soomla.removeEventHandlersWithTarget = function (target) {
    _.forEach(Soomla.eventHandlers, function (handlers, eventName) {
      var filteredArray = _.filter(handlers, function (callbackObject) {
        return (callbackObject.obj != target);
      });
      Soomla.eventHandlers[eventName] = filteredArray;
    });
  };

  Soomla.fireSoomlaEvent = function (eventName, args) {
    var handlersArray = Soomla.eventHandlers[eventName];
    if (handlersArray === undefined) {
      return;
    }

    _.forEach(handlersArray, function (callbackObject) {
      callbackObject.callback.apply(callbackObject.obj, args);
    });
  };

  window.ndkCallback = function (parameters) {
    parameters = JSON.parse(parameters);
    try {
      Soomla.soomlaEventDispatcher.ndkCallback(parameters);
    } catch (e) {
      Soomla.logError("ndkCallback: " + e.message);
    }
  };

  var StoreBridge = Soomla.StoreBridge = declareClass("StoreBridge", {
    init: function () {
      return true;
    },
    applyParams: function applyParams(storeParams) {
    }
  });


  function SoomlaException(code, message) {
    this.name = "SoomlaException";
    this.code = code || 0;
    this.message = (message || "");
  }

  SoomlaException.prototype = Error.prototype;
  SoomlaException.CODE = {
    ITEM_NOT_FOUND: -1,
    INSUFFICIENT_FUNDS: -2,
    NOT_ENOUGH_GOODS: -3,
    OTHER: -4
  };

  var removeNulls = function removeNulls(key, value) {
    if (!value) {
      return undefined;
    }

    return value;
  };

  Soomla.callNative = function callNative(params, clean) {
    var jsonString = null;

    var result;

    if (Soomla.platform.isNativeSupported()) {
      if (typeof(clean) === 'undefined') {
        jsonString = Soomla.CCSoomlaNdkBridge.callNative(JSON.stringify(params));
      }
      else {
        jsonString = Soomla.CCSoomlaNdkBridge.callNative(JSON.stringify(params, removeNulls));
      }
      result = JSON.parse(jsonString);
    } else {
      result = {success: true, 'return': {}};
    }

    if (!result.success) {
      throw new SoomlaException(result.code, result.info);
    }
    return result.result;
  };

  Soomla.logDebug = function (output) {
    if (Soomla.DEBUG) {
      console.log("DEBUG: " + output);
    }
  };

  Soomla.logError = function (output) {
    console.log("ERROR: " + output);
  };

  Soomla.dumpError = function dumpError(e) {
    return e + " : " + JSON.stringify(e);
  };

  Soomla.dump = function dump(obj) {
    return JSON.stringify(obj);
  };


  var CoreEventDispatcher = Soomla.CoreEventDispatcher = function () {

    var CoreEventDispatcher = Soomla.declareClass('CoreEventDispatcher', {
      init: function () {
        var eventDispatcher = Soomla.soomlaEventDispatcher;

        eventDispatcher.registerEventHandler(CoreConsts.EVENT_REWARD_GIVEN, _.bind(function (parameters) {
          var rewardId = parameters['reward'];
          var reward = Soomla.Models.Reward.getReward(rewardId);
          Soomla.fireSoomlaEvent(parameters.method, [reward]);
        }, this));

        eventDispatcher.registerEventHandler(Soomla.Models.CoreConsts.EVENT_REWARD_TAKEN, _.bind(function (parameters) {
          var rewardId = parameters['reward'];
          var reward = Soomla.Models.Reward.getReward(rewardId);
          Soomla.fireSoomlaEvent(parameters.method, [reward]);
        }, this));

        eventDispatcher.registerEventHandler(Soomla.Models.CoreConsts.EVENT_CUSTOM, _.bind(function (parameters) {
          var name = parameters['name'];
          var extra = parameters['extra'];
          Soomla.fireSoomlaEvent(parameters.method, [name, extra]);
        }, this));

        return true;
      }
    });

    CoreEventDispatcher.initShared = function () {
      var ret = CoreEventDispatcher.create();
      if (ret.init()) {
        Soomla.coreEventDispatcher = ret;
      } else {
        Soomla.coreEventDispatcher = null;
      }
    };

    return CoreEventDispatcher;
  }();

  return Soomla
})();
