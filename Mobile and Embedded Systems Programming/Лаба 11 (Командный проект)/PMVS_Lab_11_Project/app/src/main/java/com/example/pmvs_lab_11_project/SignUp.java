package com.example.pmvs_lab_11_project;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class SignUp extends AppCompatActivity {
    EditText etMail, pswd, pswd_conf;
    Button sign_up_btn;
    Intent intent_sign_in;
    SharedPreferences pref;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.sign_up);
        etMail = (EditText)findViewById(R.id.etEmail);
        pswd = (EditText)findViewById(R.id.etPassword);
        pswd_conf = (EditText)findViewById(R.id.etPasswordConfirm);
        sign_up_btn = (Button)findViewById(R.id.btnSignUpConfirm);
        pref = getSharedPreferences(getResources().getString(R.string.DB), MODE_PRIVATE);
        intent_sign_in = new Intent(SignUp.this, com.example.pmvs_lab_11_project.MainActivity.class);
        sign_up_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SharedPreferences mSettings = getSharedPreferences(getResources().getString(R.string.DB), Context.MODE_PRIVATE);
                String username = etMail.getText().toString();
                String password = pswd.getText().toString();
                String password_2 = pswd_conf.getText().toString();
                if (mSettings.contains(username)){
                    Toast.makeText(getApplicationContext(),"Аккаунт с такой почтой уже существует",Toast.LENGTH_SHORT).show();
                }
                else
                {
                    if (username.contains("@"))
                    {
                        if (password.length() > 7)
                        {
                            if (password.equals(password_2))
                            {
                                if (password.contains("/"))
                                {
                                    Toast.makeText(getApplicationContext(),"В пароле недопустимые символы",Toast.LENGTH_SHORT).show();
                                }
                                else
                                {
                                    SharedPreferences.Editor editor = pref.edit();
                                    editor.putString(username, (password + "/0/0/0"));
                                    editor.apply();
                                    Toast.makeText(getApplicationContext(), "Успешная регистрация",Toast.LENGTH_SHORT).show();
                                    startActivity(intent_sign_in);
                                }
                            }
                            else
                            {
                                Toast.makeText(getApplicationContext(),"Пароли не совпадают",Toast.LENGTH_SHORT).show();
                            }
                        }
                        else
                        {
                            Toast.makeText(getApplicationContext(),"Пароль слишком короткий (< 8)",Toast.LENGTH_SHORT).show();
                        }
                    }
                    else
                    {
                        Toast.makeText(getApplicationContext(),"Почта введена некорректно",Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });
    }
}
