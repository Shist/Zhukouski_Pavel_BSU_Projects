package com.example.pmvs_lab_6_3_3_var_4_kotlin

import android.os.Bundle
import android.view.View
import android.widget.ArrayAdapter
import android.widget.EditText
import android.widget.Spinner
import androidx.appcompat.app.AppCompatActivity
import java.util.*

class MainActivity : AppCompatActivity() {
    var spinner1: Spinner? = null
    var spinner2: Spinner? = null
    var etInput1: EditText? = null
    var etInput2: EditText? = null
    var CurrencyList =
        arrayOf("USD", "EUR", "JPY", "GBP", "AUD", "CAD", "CHF", "RUB", "BLR", "UAH")
    var CoefficientList =
        doubleArrayOf(1.0, 0.8457, 104.94, 0.7586, 1.37, 1.3, 0.9122, 76.31, 2.58, 28.11)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        spinner1 = findViewById<View>(R.id.spinner1) as Spinner
        val adapter =
            ArrayAdapter(this, android.R.layout.simple_spinner_item, CurrencyList)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        spinner1!!.adapter = adapter
        spinner2 = findViewById<View>(R.id.spinner2) as Spinner
        val adapter2 =
            ArrayAdapter(this, android.R.layout.simple_spinner_item, CurrencyList)
        adapter2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        spinner2!!.adapter = adapter
        etInput1 = findViewById<View>(R.id.editText1) as EditText
        etInput2 = findViewById<View>(R.id.editText2) as EditText
    }

    fun Num_0_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "0")
    }

    fun Num_1_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "1")
    }

    fun Num_2_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "2")
    }

    fun Num_3_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "3")
    }

    fun Num_4_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "4")
    }

    fun Num_5_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "5")
    }

    fun Num_6_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "6")
    }

    fun Num_7_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "7")
    }

    fun Num_8_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "8")
    }

    fun Num_9_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + "9")
    }

    fun Dot_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + ".")
    }

    fun Clear_onClick(v: View?) {
        etInput1!!.setText("")
    }

    fun Plus_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + " + ")
    }

    fun Minus_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + " - ")
    }

    fun Multiply_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + " * ")
    }

    fun Divide_onClick(v: View?) {
        etInput1!!.setText(etInput1!!.text.toString() + " / ")
    }

    fun Calculate_onClick(v: View?) {
        val expr = etInput1!!.text.toString()
        if (expr == "") {
            etInput2?.setText(R.string.error_nothing)
            return
        }
        val current_currency_name1 = spinner1!!.selectedItem.toString()
        val index1 =
            Arrays.asList(*CurrencyList).indexOf(current_currency_name1)
        val coefficient1 = CoefficientList[index1]
        val current_currency_name2 = spinner2!!.selectedItem.toString()
        val index2 =
            Arrays.asList(*CurrencyList).indexOf(current_currency_name2)
        val coefficient2 = CoefficientList[index2]
        val result =
            coefficient2 / coefficient1 * eval(expr)
        if (java.lang.Double.isInfinite(result) || java.lang.Double.isNaN(result)) {
            etInput2?.setText(R.string.error_zero)
            return
        }
        etInput2!!.setText(String.format(Locale.US, "%f", result))
    }

    companion object {
        // Позаимствовал данную функцию для подсчёта математических выражений в виде строк на Java вот из этого источника:
        // https://fooobar.com/questions/28238/evaluating-a-math-expression-given-in-string-form
        fun eval(str: String): Double {
            return object : Any() {
                var pos = -1
                var ch = 0
                fun nextChar() {
                    ch = if (++pos < str.length) str[pos].toInt() else -1
                }

                fun eat(charToEat: Int): Boolean {
                    while (ch == ' '.toInt()) nextChar()
                    if (ch == charToEat) {
                        nextChar()
                        return true
                    }
                    return false
                }

                fun parse(): Double {
                    nextChar()
                    val x = parseExpression()
                    if (pos < str.length) throw RuntimeException("Unexpected: " + ch.toChar())
                    return x
                }

                // Grammar:
                // expression = term | expression `+` term | expression `-` term
                // term = factor | term `*` factor | term `/` factor
                // factor = `+` factor | `-` factor | `(` expression `)`
                //        | number | functionName factor | factor `^` factor
                fun parseExpression(): Double {
                    var x = parseTerm()
                    while (true) {
                        if (eat('+'.toInt())) x += parseTerm() // addition
                        else if (eat('-'.toInt())) x -= parseTerm() // subtraction
                        else return x
                    }
                }

                fun parseTerm(): Double {
                    var x = parseFactor()
                    while (true) {
                        if (eat('*'.toInt())) x *= parseFactor() // multiplication
                        else if (eat('/'.toInt())) x /= parseFactor() // division
                        else return x
                    }
                }

                fun parseFactor(): Double {
                    if (eat('+'.toInt())) return parseFactor() // unary plus
                    if (eat('-'.toInt())) return -parseFactor() // unary minus
                    var x: Double
                    val startPos = pos
                    if (eat('('.toInt())) { // parentheses
                        x = parseExpression()
                        eat(')'.toInt())
                    } else if (ch >= '0'.toInt() && ch <= '9'.toInt() || ch == '.'.toInt()) { // numbers
                        while (ch >= '0'.toInt() && ch <= '9'.toInt() || ch == '.'.toInt()) nextChar()
                        x =
                            str.substring(startPos, pos)
                                .toDouble()
                    } else if (ch >= 'a'.toInt() && ch <= 'z'.toInt()) { // functions
                        while (ch >= 'a'.toInt() && ch <= 'z'.toInt()) nextChar()
                        val func =
                            str.substring(startPos, pos)
                        x = parseFactor()
                        if (func == "sqrt") x =
                            Math.sqrt(x) else if (func == "sin") x =
                            Math.sin(Math.toRadians(x)) else if (func == "cos") x =
                            Math.cos(Math.toRadians(x)) else if (func == "tan") x =
                            Math.tan(Math.toRadians(x)) else throw RuntimeException(
                            "Unknown function: " + func
                        )
                    } else {
                        throw RuntimeException("Unexpected: " + ch.toChar())
                    }
                    if (eat('^'.toInt())) x = Math.pow(
                        x,
                        parseFactor()
                    ) // exponentiation
                    return x
                }
            }.parse()
        }
    }
}