package com.example.pmvs_lab_6_3_2

import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import java.util.*

class MainActivity : AppCompatActivity() {
    var tvInfo: TextView? = null
    var etInput: EditText? = null
    var bControl: Button? = null
    var need_num = 0 // from 1 to 200
    var game_over = false // game over or not

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        tvInfo = findViewById<View>(R.id.textView1) as TextView
        etInput = findViewById<View>(R.id.editText1) as EditText
        bControl = findViewById<View>(R.id.button1) as Button
        tvInfo!!.text = resources.getString(R.string.try_to_guess)
        bControl!!.text = resources.getString(R.string.input_value)
        val rand = Random()
        need_num = rand.nextInt(200) + 1 // [1, ..., 200]
        game_over = false
    }

    fun onClick(v: View?) {
        if (etInput!!.text.toString() == "") { // Если строка с числом пуста
            tvInfo!!.text = resources.getString(R.string.error_empty_str)
            return
        }
        val guess_num = etInput!!.text.toString().toInt()
        if (guess_num > 200) {
            tvInfo!!.text = resources.getString(R.string.error_too_big)
            etInput!!.setText("")
            return
        }
        if (guess_num < 1) {
            tvInfo!!.text = resources.getString(R.string.error_too_small)
            etInput!!.setText("")
            return
        }
        if (guess_num < need_num) {
            tvInfo!!.text = resources.getString(R.string.behind)
            etInput!!.setText("")
        } else if (guess_num > need_num) {
            tvInfo!!.text = resources.getString(R.string.ahead)
            etInput!!.setText("")
        } else {
            tvInfo!!.text = resources.getString(R.string.hit)
            game_over = true
        }
    }

    fun playMore(v: View?) {
        tvInfo!!.text = resources.getString(R.string.try_to_guess)
        bControl!!.text = resources.getString(R.string.input_value)
        etInput!!.setText("")
        val rand = Random()
        need_num = rand.nextInt(200) + 1 // [1, ..., 200]
        game_over = false
    }
}