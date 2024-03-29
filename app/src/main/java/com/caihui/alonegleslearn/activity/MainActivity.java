package com.caihui.alonegleslearn.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

import com.caihui.alonegleslearn.R;

public class MainActivity extends AppCompatActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.bt_hello_triangle).setOnClickListener(v -> startActivity(new Intent(MainActivity.this, HelloTriangleActivity.class)));
        findViewById(R.id.bt_ubo).setOnClickListener(v -> startActivity(new Intent(MainActivity.this, UboActivity.class)));
        findViewById(R.id.bt_texture).setOnClickListener(v -> startActivity(new Intent(MainActivity.this, TextureMapActivity.class)));
        findViewById(R.id.bt_yuv_map).setOnClickListener(v -> startActivity(new Intent(MainActivity.this, YuvMapActivity.class)));
        findViewById(R.id.bt_vbo).setOnClickListener(v-> startActivity(new Intent(MainActivity.this, VboEboVaoActivity.class)));
        findViewById(R.id.bt_transform).setOnClickListener(v -> startActivity(new Intent(MainActivity.this, TransformSampleActivity.class)));
    }
}