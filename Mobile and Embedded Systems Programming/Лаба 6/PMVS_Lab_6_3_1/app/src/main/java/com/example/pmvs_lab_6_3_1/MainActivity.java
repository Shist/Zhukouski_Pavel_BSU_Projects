package com.example.pmvs_lab_6_3_1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import android.view.View;
import android.widget.*;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    TextView tvInfo;
    EditText etInput;
    Button bControl;

    int need_num; // from 1 to 200
    boolean game_over; // game over or not

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvInfo = (TextView)findViewById(R.id.textView1);
        etInput = (EditText)findViewById(R.id.editText1);
        bControl = (Button)findViewById(R.id.button1);

        tvInfo.setText(getResources().getString(R.string.try_to_guess));
        bControl.setText(getResources().getString(R.string.input_value));

        Random rand = new Random();
        need_num = rand.nextInt(200) + 1; // [1, ..., 200]
        game_over = false;
    }

    public void onClick(View v)
    {
        if (etInput.getText().toString().equals(""))
        { // Если строка с числом пуста
            tvInfo.setText(getResources().getString(R.string.error_empty_str));
            return;
        }

        int guess_num = Integer.parseInt(etInput.getText().toString());

        if (guess_num > 200)
        {
            tvInfo.setText(getResources().getString(R.string.error_too_big));
            etInput.setText("");
            return;
        }

        if (guess_num < 1)
        {
            tvInfo.setText(getResources().getString(R.string.error_too_small));
            etInput.setText("");
            return;
        }

        if (guess_num < need_num)
        {
            tvInfo.setText(getResources().getString(R.string.behind));
            etInput.setText("");
        }
        else if (guess_num > need_num)
        {
            tvInfo.setText(getResources().getString(R.string.ahead));
            etInput.setText("");
        }
        else {
            tvInfo.setText(getResources().getString(R.string.hit));
            game_over = true;
        }
    }

    public void playMore(View v)
    {
        tvInfo.setText(getResources().getString(R.string.try_to_guess));
        bControl.setText(getResources().getString(R.string.input_value));
        etInput.setText("");

        Random rand = new Random();
        need_num = rand.nextInt(200) + 1; // [1, ..., 200]
        game_over = false;
    }
}