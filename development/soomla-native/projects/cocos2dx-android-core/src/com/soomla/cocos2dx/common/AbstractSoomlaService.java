package com.soomla.cocos2dx.common;

import android.opengl.GLSurfaceView;

import java.lang.ref.WeakReference;

/**
 * @author vedi
 *         date 7/1/14
 *         time 1:11 PM
 */
public abstract class AbstractSoomlaService implements SoomlaService {

    protected static WeakReference<GLSurfaceView> glSurfaceViewRef = new WeakReference<GLSurfaceView>(null);

    @Override
    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        glSurfaceViewRef = new WeakReference<GLSurfaceView>(glSurfaceView);
    }

    @Override
    public void onPause() {

    }

    @Override
    public void onResume() {

    }
}
