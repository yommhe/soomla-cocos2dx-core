package com.soomla.cocos2dx.common;

import android.opengl.GLSurfaceView;

/**
 * @author vedi
 *         date 7/1/14
 *         time 10:44 AM
 */
public interface SoomlaService {
    void setGlSurfaceView(GLSurfaceView glSurfaceView);
    void onPause();
    void onResume();
}
