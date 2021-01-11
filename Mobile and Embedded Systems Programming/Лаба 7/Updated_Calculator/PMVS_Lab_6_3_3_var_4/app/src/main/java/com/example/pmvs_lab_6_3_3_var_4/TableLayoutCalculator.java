package com.example.pmvs_lab_6_3_3_var_4;

import android.app.Dialog;
import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Arrays;
import java.util.Locale;

public class TableLayoutCalculator extends AppCompatActivity {

    Spinner spinner1;
    Spinner spinner2;

    EditText etInput1;
    EditText etInput2;

    String[] CurrencyList = {"USD", "EUR", "JPY", "GBP", "AUD", "CAD", "CHF", "RUB", "BLR", "UAH"};
    double[] CoefficientList = {1.0, 0.8457, 104.94, 0.7586, 1.37, 1.3, 0.9122, 76.31, 2.58, 28.11};

    Dialog dial; // For dialog windows

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.table_layout_calculator);

        spinner1 = (Spinner) findViewById(R.id.spinner1);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, CurrencyList);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner1.setAdapter(adapter);

        spinner2 = (Spinner) findViewById(R.id.spinner2);
        ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, CurrencyList);
        adapter2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner2.setAdapter(adapter);

        etInput1 = (EditText)findViewById(R.id.editText1);

        etInput2 = (EditText)findViewById(R.id.editText2);

        dial = new Dialog(TableLayoutCalculator.this);
    }

    public void Num_0_onClick(View v) { etInput1.setText((etInput1.getText().toString() + "0"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);}

    public void Num_1_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "1"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Num_2_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "2"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Num_3_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "3"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Num_4_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "4"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Num_5_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "5"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Num_6_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "6"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Num_7_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "7"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Num_8_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "8"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Num_9_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "9"));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Dot_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + "."));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Clear_onClick(View v)
    {
        etInput1.setText("");
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Plus_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + " + "));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Minus_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + " - "));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Multiply_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + " * "));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Divide_onClick(View v)
    {
        etInput1.setText((etInput1.getText().toString() + " / "));
        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    public void Calculate_onClick(View v)
    {
        String expr = etInput1.getText().toString();

        if (expr.equals(""))
        {
            etInput2.setText(R.string.error_nothing);
            // Заголовок
            dial.setTitle("Error!");
            // Ссылка на разметку
            dial.setContentView(R.layout.dialog);
            // Установка текста в окне
            TextView text = (TextView) dial.findViewById(R.id.DialogView);
            text.setText((getResources().getString(R.string.error_nothing)));
            dial.show();
            return;
        }

        String current_currency_name1 = spinner1.getSelectedItem().toString();
        int index1 = Arrays.asList(CurrencyList).indexOf(current_currency_name1);
        double coefficient1 = CoefficientList[index1];

        String current_currency_name2 = spinner2.getSelectedItem().toString();
        int index2 = Arrays.asList(CurrencyList).indexOf(current_currency_name2);
        double coefficient2 = CoefficientList[index2];

        double result = (coefficient2 / coefficient1)*eval(expr);

        if (Double.isInfinite(result) || Double.isNaN(result))
        {
            etInput2.setText(R.string.error_zero);
            dial.setTitle("Error!");
            // Ссылка на разметку
            dial.setContentView(R.layout.dialog);
            // Установка текста в окне
            TextView text = (TextView) dial.findViewById(R.id.DialogView);
            text.setText((getResources().getString(R.string.error_zero)));
            dial.show();
            return;
        }

        etInput2.setText(String.format(Locale.US,"%f", result));

        Animation a = AnimationUtils.loadAnimation(this, R.anim.flicker);
        a.reset();
        v.clearAnimation();
        v.startAnimation(a);
    }

    // Позаимствовал данную функцию для подсчёта математических выражений в виде строк на Java вот из этого источника:
    // https://fooobar.com/questions/28238/evaluating-a-math-expression-given-in-string-form
    public static double eval(final String str) {
        return new Object() {
            int pos = -1, ch;

            void nextChar() {
                ch = (++pos < str.length()) ? str.charAt(pos) : -1;
            }

            boolean eat(int charToEat) {
                while (ch == ' ') nextChar();
                if (ch == charToEat) {
                    nextChar();
                    return true;
                }
                return false;
            }

            double parse() {
                nextChar();
                double x = parseExpression();
                if (pos < str.length()) throw new RuntimeException("Unexpected: " + (char)ch);
                return x;
            }

            // Grammar:
            // expression = term | expression `+` term | expression `-` term
            // term = factor | term `*` factor | term `/` factor
            // factor = `+` factor | `-` factor | `(` expression `)`
            //        | number | functionName factor | factor `^` factor

            double parseExpression() {
                double x = parseTerm();
                for (;;) {
                    if      (eat('+')) x += parseTerm(); // addition
                    else if (eat('-')) x -= parseTerm(); // subtraction
                    else return x;
                }
            }

            double parseTerm() {
                double x = parseFactor();
                for (;;) {
                    if      (eat('*')) x *= parseFactor(); // multiplication
                    else if (eat('/')) x /= parseFactor(); // division
                    else return x;
                }
            }

            double parseFactor() {
                if (eat('+')) return parseFactor(); // unary plus
                if (eat('-')) return -parseFactor(); // unary minus

                double x;
                int startPos = this.pos;
                if (eat('(')) { // parentheses
                    x = parseExpression();
                    eat(')');
                } else if ((ch >= '0' && ch <= '9') || ch == '.') { // numbers
                    while ((ch >= '0' && ch <= '9') || ch == '.') nextChar();
                    x = Double.parseDouble(str.substring(startPos, this.pos));
                } else if (ch >= 'a' && ch <= 'z') { // functions
                    while (ch >= 'a' && ch <= 'z') nextChar();
                    String func = str.substring(startPos, this.pos);
                    x = parseFactor();
                    if (func.equals("sqrt")) x = Math.sqrt(x);
                    else if (func.equals("sin")) x = Math.sin(Math.toRadians(x));
                    else if (func.equals("cos")) x = Math.cos(Math.toRadians(x));
                    else if (func.equals("tan")) x = Math.tan(Math.toRadians(x));
                    else throw new RuntimeException("Unknown function: " + func);
                } else {
                    throw new RuntimeException("Unexpected: " + (char)ch);
                }

                if (eat('^')) x = Math.pow(x, parseFactor()); // exponentiation

                return x;
            }
        }.parse();
    }
}