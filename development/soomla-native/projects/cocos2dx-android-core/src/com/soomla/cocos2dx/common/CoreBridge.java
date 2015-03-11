package com.soomla.cocos2dx.common;

import android.opengl.GLSurfaceView;

import com.soomla.Soomla;
import com.soomla.SoomlaUtils;
import com.soomla.data.KeyValueStorage;
import com.soomla.data.RewardStorage;
import com.soomla.rewards.BadgeReward;
import com.soomla.rewards.RandomReward;
import com.soomla.rewards.SequenceReward;
import com.soomla.Schedule;
import org.json.JSONException;
import org.json.JSONObject;

public class CoreBridge {

    private static CoreBridge INSTANCE = null;

    public static CoreBridge getInstance() {
        if (INSTANCE == null) {
            synchronized (CoreBridge.class) {
                if (INSTANCE == null) {
                    INSTANCE = new CoreBridge();
                }
            }
        }
        return INSTANCE;
    }

    @SuppressWarnings("FieldCanBeLocal")
    private CoreEventHandlerBridge coreEventHandlerBridge;

    public CoreBridge() {
        coreEventHandlerBridge = new CoreEventHandlerBridge();

        DomainHelper.getInstance().registerTypeWithClassName(CommonConsts.JSON_JSON_TYPE_SCHEDULE, Schedule.class);
        DomainHelper.getInstance().registerTypeWithClassName(CommonConsts.JSON_JSON_TYPE_DATE_TIME_RANGE, Schedule.DateTimeRange.class);

        final DomainFactory domainFactory = DomainFactory.getInstance();

        domainFactory.registerCreator(CommonConsts.JSON_JSON_TYPE_BADGE, new DomainFactory.Creator<BadgeReward>() {
            @Override
            public BadgeReward create(JSONObject jsonObject) {
                try {
                    return new BadgeReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
        domainFactory.registerCreator(CommonConsts.JSON_JSON_TYPE_RANDOM, new DomainFactory.Creator<RandomReward>() {
            @Override
            public RandomReward create(JSONObject jsonObject) {
                try {
                    return new RandomReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
        domainFactory.registerCreator(CommonConsts.JSON_JSON_TYPE_SEQUENCE, new DomainFactory.Creator<SequenceReward>() {
            @Override
            public SequenceReward create(JSONObject jsonObject) {
                try {
                    return new SequenceReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });

        final NdkGlue ndkGlue = NdkGlue.getInstance();

        ndkGlue.registerCallHandler("CCSoomla::initialize", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String customSecret = params.optString("customSecret");
                SoomlaUtils.LogDebug("SOOMLA", "initialize is called from java!");
                Soomla.initialize(customSecret);
            }
        });
        ndkGlue.registerCallHandler("CCCoreBridge::getTimesGiven", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String rewardId = params.getString("reward");
                int result = RewardStorage.getTimesGiven(rewardId);
                retParams.put("return", result);
            }
        });
        ndkGlue.registerCallHandler("CCCoreBridge::setRewardStatus", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String rewardId = params.getString("reward");
                boolean give =  params.getBoolean("give");
                boolean notify =  params.getBoolean("notify");
                RewardStorage.setRewardStatus(rewardId, give, notify);
            }
        });
        ndkGlue.registerCallHandler("CCCoreBridge::getLastSeqIdxGiven", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String rewardId = params.getString("reward");
                int result = RewardStorage.getLastSeqIdxGiven(rewardId);
                retParams.put("return", result);
            }
        });
        ndkGlue.registerCallHandler("CCCoreBridge::setLastSeqIdxGiven", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String rewardId = params.getString("reward");
                int idx =  params.getInt("idx");
                RewardStorage.setLastSeqIdxGiven(rewardId, idx);
            }
        });

        ndkGlue.registerCallHandler("CCCoreBridge::getValue", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String key =  params.getString("key");
                String result = KeyValueStorage.getValue(key);
                retParams.put("return", result);
            }
        });
        ndkGlue.registerCallHandler("CCCoreBridge::setValue", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String key =  params.getString("key");
                String val =  params.getString("val");
                KeyValueStorage.setValue(key, val);
            }
        });
        ndkGlue.registerCallHandler("CCCoreBridge::deleteKeyValue", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                String key =  params.getString("key");
                KeyValueStorage.deleteKeyValue(key);
            }
        });
        ndkGlue.registerCallHandler("CCCoreBridge::purge", new NdkGlue.CallHandler() {
            @Override
            public void handle(JSONObject params, JSONObject retParams) throws Exception {
                KeyValueStorage.purge();
            }
        });
    }

    public void init() {
        final GLSurfaceView glSurfaceView = NdkGlue.getInstance().getGlSurfaceRef().get();
        if (glSurfaceView != null) {
            coreEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        }
    }
}
