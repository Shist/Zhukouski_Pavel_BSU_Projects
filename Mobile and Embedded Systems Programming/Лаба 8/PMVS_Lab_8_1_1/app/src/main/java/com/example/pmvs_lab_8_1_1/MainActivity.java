package com.example.pmvs_lab_8_1_1;
import android.os.Bundle;
import android.app.Activity;
import androidx.core.view.GestureDetectorCompat;
import android.view.*;
import android.widget.*;

public class MainActivity extends Activity
        implements GestureDetector.OnGestureListener,
        GestureDetector.OnDoubleTapListener
{
    TextView tvOutput;
    GestureDetectorCompat mDetector;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tvOutput = (TextView)findViewById(R.id.TextView1);
        mDetector = new GestureDetectorCompat(this,this);
        mDetector.setOnDoubleTapListener(this);
    }
    public boolean onTouchEvent(MotionEvent event){
        this.mDetector.onTouchEvent(event);
// Be sure to call the superclass implementation
        return super.onTouchEvent(event);
    }
    @Override
    public boolean onDown(MotionEvent event) {
        tvOutput.setText(("onDown: " + event.toString()));
        return false;
    }
    @Override
    public boolean onFling(MotionEvent event1, MotionEvent event2,
                           float velocityX, float velocityY) {
        tvOutput.setText(("onFling: " + event1.toString()+event2.toString()));
        return true;
    }
    @Override
    public void onLongPress(MotionEvent event) {
        tvOutput.setText(("onLongPress: " + event.toString()));
    }
    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX,
                            float distanceY) {
        tvOutput.setText(("onScroll: " + e1.toString()+e2.toString()));
        return true;
    }
    @Override
    public void onShowPress(MotionEvent event) {
        tvOutput.setText(("onShowPress: " + event.toString()));
    }
    @Override
    public boolean onSingleTapUp(MotionEvent event) {
        tvOutput.setText(("onSingleTapUp: " + event.toString()));
        return true;
    }
    @Override
    public boolean onDoubleTap(MotionEvent event) {
        tvOutput.setText(("onDoubleTap: " + event.toString()));
        return true;
    }
    @Override
    public boolean onDoubleTapEvent(MotionEvent event) {
        tvOutput.setText(("onDoubleTapEvent: " + event.toString()));
        return true;
    }
    @Override
    public boolean onSingleTapConfirmed(MotionEvent event) {
        tvOutput.setText(("onSingleTapConfirmed: " + event.toString()));
        return true;
    }
}