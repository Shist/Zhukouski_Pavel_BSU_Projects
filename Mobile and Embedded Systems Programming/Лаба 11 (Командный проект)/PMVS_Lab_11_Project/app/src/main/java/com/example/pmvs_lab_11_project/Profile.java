package com.example.pmvs_lab_11_project;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;

public class Profile extends AppCompatActivity {

    TextView nameLabel;
    TextView bestScoreLabel;
    TextView avgSpeedLabel;
    TextView countLabel;
    Button exit_btn;
    Button start_btn;
    Intent intent_sign_in;
    Intent intent_start;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.profile);
        nameLabel = (TextView) findViewById(R.id.userName);
        bestScoreLabel = (TextView) findViewById(R.id.bestScore);
        avgSpeedLabel = (TextView) findViewById(R.id.avrSpeed);
        countLabel = (TextView) findViewById(R.id.count);
        exit_btn = (Button)findViewById(R.id.btnSignOut);
        start_btn = (Button)findViewById(R.id.btnStartTraining);
        intent_sign_in = new Intent(Profile.this, com.example.pmvs_lab_11_project.MainActivity.class);
        intent_start = new Intent(Profile.this, com.example.pmvs_lab_11_project.TrainingWindow.class);
        Bundle arguments = getIntent().getExtras();
        String user = arguments.get("username").toString();
        intent_start.putExtra("username", user);
        SharedPreferences mSettings = getSharedPreferences(getResources().getString(R.string.DB), Context.MODE_PRIVATE);
        String[] user_info = mSettings.getString(user, "").split("/");
        String[] user_name = user.split("@");
        nameLabel.setText(user_name[0]);
        intent_start.putExtra("password", user_info[0]);
        bestScoreLabel.setText((user_info[1] + " зн/мин"));
        intent_start.putExtra("record", user_info[1]);
        avgSpeedLabel.setText((user_info[2] + " зн/мин"));
        intent_start.putExtra("avg_speed", user_info[2]);
        countLabel.setText(user_info[3]);
        intent_start.putExtra("count", user_info[3]);

        Animation a = AnimationUtils.loadAnimation(this, R.anim.increase);
        a.reset();
        start_btn.clearAnimation();
        start_btn.startAnimation(a);
        start_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(intent_start);
            }
        });
        exit_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(intent_sign_in);
            }
        });
    }
}
