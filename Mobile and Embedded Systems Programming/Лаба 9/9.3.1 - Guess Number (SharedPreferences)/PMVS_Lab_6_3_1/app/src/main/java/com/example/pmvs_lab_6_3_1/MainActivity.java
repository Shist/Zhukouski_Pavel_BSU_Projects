package com.example.pmvs_lab_6_3_1;

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
import static android.content.Context.MODE_PRIVATE;

public class MainActivity extends AppCompatActivity {
    TextView launchesCountTextView;
    EditText etMail, pswd;
    Button sign_in_btn;
    SharedPreferences pref;
    Intent intent;
    int launchesCount;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.sign_in);
        launchesCountTextView = (TextView)findViewById(R.id.launchesCountTextView);
        etMail = (EditText)findViewById(R.id.etEmail);
        pswd = (EditText)findViewById(R.id.etPassword);
        sign_in_btn = (Button)findViewById(R.id.btnPlay);
        Animation a = AnimationUtils.loadAnimation(this, R.anim.increase);
        a.reset();
        sign_in_btn.clearAnimation();
        sign_in_btn.startAnimation(a);
        pref = getSharedPreferences("user_details",MODE_PRIVATE);
        launchesCount = pref.getInt("launches", 0);
        launchesCount++;
        launchesCountTextView.setText(("Количество запусков приложения: " + launchesCount));
        intent = new Intent(MainActivity.this, com.example.pmvs_lab_6_3_1.GameActivity.class);
        if(pref.contains("username") && pref.contains("password")){
            startActivity(intent);
        }
        sign_in_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String username = etMail.getText().toString();
                String password = pswd.getText().toString();
                if(username.equals("shist.pupust@mail.ru") && password.equals("1823361")){
                    SharedPreferences.Editor editor = pref.edit();
                    editor.putString("username", username);
                    editor.putString("password", password);
                    editor.putInt("launches", launchesCount);
                    editor.apply();

                    Toast.makeText(getApplicationContext(), "Login Successful",Toast.LENGTH_SHORT).show();
                    startActivity(intent);
                }
                else
                {
                    Toast.makeText(getApplicationContext(),"Credentials are not valid",Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}