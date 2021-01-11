package com.example.pmvs_lab_8_3_1;
import android.os.Bundle;
import android.app.Activity;
import androidx.core.view.*;
import android.view.*;
import android.widget.*;
import android.widget.RelativeLayout;

public class MainActivity extends Activity {
    private GestureDetectorCompat mDetector;
    public RelativeLayout relativeLayout;
    private TextView tvOut;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mDetector = new GestureDetectorCompat(this, new MyGestListener());
        tvOut = (TextView)findViewById(R.id.TextView1);
        relativeLayout = (RelativeLayout)findViewById(R.id.relativelayout);
        relativeLayout.setBackgroundResource(R.color.black);
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
            if (event1.getRawX() < 1200 && event1.getRawX() >= 1030)
            {
                relativeLayout.setBackgroundResource(R.color.purple);
                tvOut.setText(R.string.purple);
            }
            else if (event1.getRawX() < 1030 && event1.getRawX() >= 860)
            {
                relativeLayout.setBackgroundResource(R.color.dark_blue);
                tvOut.setText(R.string.dark_blue);
            }
            else if (event1.getRawX() < 860 && event1.getRawX() >= 690)
            {
                relativeLayout.setBackgroundResource(R.color.light_blue);
                tvOut.setText(R.string.light_blue);
            }
            else if (event1.getRawX() < 690 && event1.getRawX() >= 520)
            {
                relativeLayout.setBackgroundResource(R.color.green);
                tvOut.setText(R.string.green);
            }
            else if (event1.getRawX() < 520 && event1.getRawX() >= 350)
            {
                relativeLayout.setBackgroundResource(R.color.yellow);
                tvOut.setText(R.string.yellow);
            }
            else if (event1.getRawX() < 350 && event1.getRawX() >= 180)
            {
                relativeLayout.setBackgroundResource(R.color.orange);
                tvOut.setText(R.string.orange);
            }else if (event1.getRawX() < 180)
            {
                relativeLayout.setBackgroundResource(R.color.red);
                tvOut.setText(R.string.red);
            }
            return true;
        }
    }
}