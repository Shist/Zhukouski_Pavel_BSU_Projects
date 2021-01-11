package com.example.pmvs_lab_11_project;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import org.w3c.dom.Text;


public class TrainingWindow extends AppCompatActivity {

    String[] textVariants = new String[5];
    int[] textSizes = new int[5];

    TextView given_text;
    TextView msg_dialog;
    EditText print_text;

    Button btn_finish;
    Button btn_exit;

    Intent intent_profile;

    Animation animAlpha;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        long start_time = System.currentTimeMillis();
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        given_text = (TextView) findViewById(R.id.inputText);
        msg_dialog = (TextView) findViewById(R.id.msgsWhilePrintingLbl);
        print_text = (EditText) findViewById(R.id.printingTextSpace);
        btn_finish = (Button) findViewById(R.id.btnFinish);
        btn_exit = (Button) findViewById(R.id.btnExitTraining);

        animAlpha = AnimationUtils.loadAnimation(this, R.anim.flicker);

        SharedPreferences pref = getSharedPreferences(getResources().getString(R.string.DB), MODE_PRIVATE);

        textVariants [0] = "Once I was sitting and sitting and for no apparent reason suddenly thought of something that even surprised myself.";
        textVariants [1] = "I figured out how nice it would be if everything around in the world was arranged the other way around.";
        textVariants [2] = "Well, for example, so that children are in charge in all matters and adults should have to obey them in everything, in everything.";
        textVariants [3] = "In general, make adults like children and children like adults.";
        textVariants [4] = "That would be great, it would be very interesting.";

        textSizes[0] = 115;
        textSizes[1] = 103;
        textSizes[2] = 130;
        textSizes[3] = 63;
        textSizes[4] = 50;

        intent_profile = new Intent(TrainingWindow.this, com.example.pmvs_lab_11_project.Profile.class);

        int rnd = (int)(Math.random() * 5);

        Animation a = AnimationUtils.loadAnimation(this, R.anim.increase);
        a.reset();

        given_text.setText(textVariants[rnd]);

        btn_exit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(intent_profile);
            }
        });

        btn_finish.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (print_text.getText().toString().equals(given_text.getText().toString()))
                {
                    btn_finish.setEnabled(false);
                    btn_exit.clearAnimation();
                    btn_exit.startAnimation(a);
                    double print_time = (double) (System.currentTimeMillis() - start_time) / 1000;
                    int symbs = textSizes[rnd];
                    double training_result = (double)symbs/print_time * 60;
                    msg_dialog.setText(("Всего символов: " + symbs + "\nВремя: " + print_time +
                            " секунд\nСкорость: " + training_result + "  зн/мин"));
                    SharedPreferences.Editor editor = pref.edit();
                    Bundle arguments = getIntent().getExtras();
                    double curr_best_score = Double.parseDouble(arguments.get("record").toString());
                    String user = arguments.get("username").toString();
                    String pwd = arguments.get("password").toString();
                    if (training_result > curr_best_score)
                    {
                        curr_best_score = training_result;
                    }
                    double curr_avg_speed = Double.parseDouble(arguments.get("avg_speed").toString());
                    int curr_count = Integer.parseInt(arguments.get("count").toString());
                    curr_count++;
                    curr_avg_speed = (curr_avg_speed + training_result) / curr_count;
                    editor.putString(user, (pwd + "/" + curr_best_score + "/" + curr_avg_speed + "/" + curr_count));
                    editor.apply();
                }
                else
                {
                    msg_dialog.setText("В введённом тексте есть ошибки");
                    Toast.makeText(getApplicationContext(),"В введённом тексте есть ошибки",Toast.LENGTH_SHORT).show();
                }
            }
        });

    }
}
