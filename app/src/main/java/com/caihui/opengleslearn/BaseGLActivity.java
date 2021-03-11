package com.caihui.opengleslearn;

import android.content.Context;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.util.AttributeSet;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.caihui.opengleslearn.view.GLRootView;

public abstract class BaseGLActivity extends AppCompatActivity {

    private GLRootView mRootView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mRootView = new GLRootView(this, getGLType());

    }

    @Override
    protected void onResume() {
        super.onResume();
        mRootView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mRootView.onPause();
    }

    protected abstract int getGLType();
}
