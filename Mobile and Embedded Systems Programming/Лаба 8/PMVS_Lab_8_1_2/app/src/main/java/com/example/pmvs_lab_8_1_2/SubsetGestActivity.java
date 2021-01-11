package com.example.pmvs_lab_8_1_2;
import android.os.Bundle;
import android.app.Activity;
import androidx.core.view.*;
import android.view.*;
import android.widget.*;

public class SubsetGestActivity extends Activity {
    private GestureDetectorCompat mDetector;
    private TextView tvOut;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_subset_gest);
        mDetector = new GestureDetectorCompat(this, new MyGestListener());
        tvOut = (TextView)findViewById(R.id.TextView1);
    }
    @Override
    public boolean onTouchEvent(MotionEvent event){
        this.mDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }
    class MyGestListener extends GestureDetector.SimpleOnGestureListener {
        @Override
        public boolean onFling(MotionEvent event1, MotionEvent event2,
                               float velocityX, float velocityY) {
            tvOut.setText(("onFling: " + event1.toString()+event2.toString()));
            return true;
        }
    }
}