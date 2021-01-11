package com.example.pmvs_lab_8_2;

import java.util.ArrayList;
import android.os.Bundle;
import android.app.Activity;
import android.gesture.Gesture;
import android.gesture.GestureLibraries;
import android.gesture.GestureLibrary;
import android.gesture.GestureOverlayView;
import android.gesture.GestureOverlayView.OnGesturePerformedListener;
import android.gesture.Prediction;
import android.view.Menu;
import android.widget.TextView;

public class Gestures extends Activity implements OnGesturePerformedListener{

    GestureLibrary gLib;
    GestureOverlayView gestures;
    TextView tvOut;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gestures);
        tvOut=(TextView)findViewById(R.id.textView1);
        //Загрузка жестов (gestures) из res/raw/gestures
        gLib = GestureLibraries.fromRawResource(this, R.raw.gestures);
        if (!gLib.load()) {
        //Если жесты не загружены, то выход из приложения
            finish();
        }
        gestures = (GestureOverlayView) findViewById(R.id.gestureOverlayView1);
        gestures.addOnGesturePerformedListener(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        // getMenuInflater().inflate(R.menu.gestures, menu);
        return true;
    }

    public void onGesturePerformed(GestureOverlayView overlay, Gesture gesture) {
        //Создаёт ArrayList c загруженными из gestures.xml жестами
        ArrayList<Prediction> predictions = gLib.recognize(gesture);
        if (predictions.size() > 0) {
            //если загружен хотя бы один жест из gestures.xml
            Prediction prediction = predictions.get(0);
            if (prediction.score > 1.0) {
                switch (prediction.name) {
                    case "one":
                        tvOut.setText("1");
                        break;
                    case "stop":
                        tvOut.setText(R.string.s);
                        break;
                    case "two":
                        tvOut.setText("2");
                        break;
                }
            } else{
                tvOut.setText("Жест неизвестен");
            }
        }
    }
}