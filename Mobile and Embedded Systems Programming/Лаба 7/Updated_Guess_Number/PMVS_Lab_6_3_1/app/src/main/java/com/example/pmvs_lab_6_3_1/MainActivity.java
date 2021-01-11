package com.example.pmvs_lab_6_3_1;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Dialog;
import android.os.Bundle;

import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.*;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    TextView tvInfo;
    EditText etInput;
    Button bControl;
    Button bPlayMore;

    int need_num; // from 1 to 200
    boolean game_over; // game over or not
    int tries_amount; // the number of tries

    Dialog dial; // For dialog windows

    Animation animAlpha;
    Animation animScale;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvInfo = (TextView)findViewById(R.id.textView1);
        etInput = (EditText)findViewById(R.id.editText1);
        bControl = (Button)findViewById(R.id.button1);
        bPlayMore = (Button)findViewById(R.id.button2);

        tvInfo.setText(getResources().getString(R.string.try_to_guess));
        bControl.setText(getResources().getString(R.string.input_value));

        Random rand = new Random();
        need_num = rand.nextInt(200) + 1; // [1, ..., 200]
        game_over = false;
        tries_amount = 0;

        dial = new Dialog(MainActivity.this);

        animAlpha = AnimationUtils.loadAnimation(this, R.anim.flicker);
        animScale = AnimationUtils.loadAnimation(this, R.anim.increase);

        Animation a = AnimationUtils.loadAnimation(this, R.anim.increase);
        a.reset();
        tvInfo.clearAnimation();
        tvInfo.startAnimation(a);
    }

    public void onClick(View v)
    {
        tries_amount++;
        String try_str = "Попытка #" + Integer.toString(tries_amount) + ": ";

        if (etInput.getText().toString().equals(""))
        { // Если строка с числом пуста
            tvInfo.setText((try_str + getResources().getString(R.string.error_empty_str)));

            // Заголовок
            dial.setTitle("Ошибка ввода");
            // Ссылка на разметку
            dial.setContentView(R.layout.dialog);
            // Установка текста в окне
            TextView text = (TextView) dial.findViewById(R.id.DialogView);
            text.setText((try_str + getResources().getString(R.string.error_empty_str)));
            dial.show();

            return;
        }

        int guess_num = Integer.parseInt(etInput.getText().toString());

        if (guess_num > 200)
        {
            tvInfo.setText((try_str + getResources().getString(R.string.error_too_big)));

            // Заголовок
            dial.setTitle("Ошибка ввода");
            // Ссылка на разметку
            dial.setContentView(R.layout.dialog);
            // Установка текста в окне
            TextView text = (TextView) dial.findViewById(R.id.DialogView);
            text.setText((try_str + getResources().getString(R.string.error_too_big)));
            dial.show();

            etInput.setText("");
            return;
        }

        if (guess_num < 1)
        {
            tvInfo.setText((try_str + getResources().getString(R.string.error_too_small)));

            // Заголовок
            dial.setTitle("Ошибка ввода");
            // Ссылка на разметку
            dial.setContentView(R.layout.dialog);
            // Установка текста в окне
            TextView text = (TextView) dial.findViewById(R.id.DialogView);
            text.setText((try_str + getResources().getString(R.string.error_too_small)));
            dial.show();

            etInput.setText("");
            return;
        }

        if (guess_num < need_num)
        {
            tvInfo.setText((try_str + getResources().getString(R.string.behind)));
            etInput.setText("");
        }
        else if (guess_num > need_num)
        {
            tvInfo.setText((try_str + getResources().getString(R.string.ahead)));
            etInput.setText("");
        }
        else {
            tvInfo.setText((try_str + getResources().getString(R.string.hit)));

            // Заголовок
            dial.setTitle("Вы выиграли!");
            // Ссылка на разметку
            dial.setContentView(R.layout.dialog);
            // Установка текста в окне
            TextView text = (TextView) dial.findViewById(R.id.DialogView);
            text.setText((getResources().getString(R.string.game_over) + "\nВаш счёт: " + tries_amount + " попыток."));
            dial.show();

            Animation a = AnimationUtils.loadAnimation(this, R.anim.increase);
            a.reset();
            bPlayMore.clearAnimation();
            bPlayMore.startAnimation(a);

            game_over = true;
        }

        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        tvInfo.clearAnimation();
        tvInfo.startAnimation(a);
    }

    public void playMore(View v)
    {
        tvInfo.setText(getResources().getString(R.string.try_to_guess));
        bControl.setText(getResources().getString(R.string.input_value));
        etInput.setText("");

        Random rand = new Random();
        need_num = rand.nextInt(200) + 1; // [1, ..., 200]
        game_over = false;
        tries_amount = 0;

        bPlayMore.clearAnimation();

        Animation a = AnimationUtils.loadAnimation(this, R.anim.increase);
        a.reset();
        tvInfo.clearAnimation();
        tvInfo.startAnimation(a);
    }
}