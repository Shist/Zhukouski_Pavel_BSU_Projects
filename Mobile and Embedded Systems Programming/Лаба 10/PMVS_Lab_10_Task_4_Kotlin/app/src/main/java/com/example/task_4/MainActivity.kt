package com.example.task_4

import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.method.ScrollingMovementMethod
import android.view.View
import android.widget.EditText
import android.widget.TextView
import androidx.annotation.RequiresApi
import com.android.volley.Request
import kotlinx.coroutines.*
import com.android.volley.toolbox.JsonObjectRequest
import com.android.volley.toolbox.Volley
import org.json.JSONObject
import java.util.*

class MainActivity : AppCompatActivity() {

    // val api_url = "https://api.openweathermap.org/data/2.5/weather?q=${city_name}&appid=77707fa03ccba27340933e99c1a31080"
    val api_url_weather_city = "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=48b533322284e9b27492fc27baf42dfe" // Погода в городе.
    val api_url_forecast = "https://api.openweathermap.org/data/2.5/forecast?q=%s&appid=48b533322284e9b27492fc27baf42dfe" // прогноз на несколько дней.
    val api_url_3_days = "pro.openweathermap.org/data/2.5/forecast/hourly?q=Minsk&appid=48b533322284e9b27492fc27baf42dfe"

    var MinskInfoLabel: TextView? = null
    var SeoulInfoLabel: TextView? = null
    var detailedCityInfoLabel: TextView? = null
    var inputCityLabel: EditText? = null

    fun getWeatherInfo(api_url: String, func_ui: (JSONObject) -> (Unit)) {
        GlobalScope.launch {
            var weatherJson: JSONObject? = null
            var isCompleted = false

            val jsonObjectRequest = JsonObjectRequest(Request.Method.GET, api_url, null,
                { response ->
                    weatherJson = response
                    isCompleted = true
                },
                { _ ->
                    // TODO: Handle error
                    isCompleted = true
                })

            val queue = Volley.newRequestQueue(applicationContext)
            queue.add(jsonObjectRequest) // Выполняем запрос.

            while (!isCompleted) {
                delay(2) // Ждём, пока не завершится наш http-request.
            }

            weatherJson?.let { func_ui(it) }

        }
    }

    fun onClickMinskInfo(v: View?) {
        getWeatherInfo("https://api.openweathermap.org/data/2.5/weather?q=Minsk&appid=48b533322284e9b27492fc27baf42dfe",
            fun(weatherJson: JSONObject) {
                runOnUiThread {
                    MinskInfoLabel!!.text = (weatherJson.getJSONObject("main").getInt("temp") - 273).toString() + " Cº"
                }
            }
        )
    }

    fun onClickSeoulInfo(v: View?) {
        getWeatherInfo("https://api.openweathermap.org/data/2.5/weather?q=Seoul&appid=48b533322284e9b27492fc27baf42dfe",
            fun(weatherJson: JSONObject) {
                runOnUiThread {
                    SeoulInfoLabel!!.text = (weatherJson.getJSONObject("main").getInt("temp") - 273).toString() + " Cº"
                }
            }
        )
    }

    @RequiresApi(Build.VERSION_CODES.O)
    fun onClickSomeCity(v: View?) {
        val city_name = inputCityLabel?.text

        getWeatherInfo(
            "https://api.openweathermap.org/data/2.5/forecast?q=${city_name}&appid=48b533322284e9b27492fc27baf42dfe",
            @RequiresApi(Build.VERSION_CODES.O)
            fun (weatherJson: JSONObject) {
                val info_str = "3 days weather forecast for: ${city_name} \n" + getForecast(weatherJson)

                runOnUiThread {
                    detailedCityInfoLabel!!.text = info_str
                }
            }
        )
    }

    fun extractDataFromJSON(weatherJSON: JSONObject): String {
        /* Вытаскиваем нужные данные из JSON. */

        val temperature = (weatherJSON.getJSONObject("main").getDouble("temp") - 273).toString()
        val feel_like_temperature = (weatherJSON.getJSONObject("main").getDouble("feels_like") - 273).toString()
        val wind_speed = (weatherJSON.getJSONObject("wind").getDouble("speed")).toString() + " m/s"

        val result = "Temperature: $temperature\n" + "feel like temperature: $feel_like_temperature\n" +
                "wind speed: $wind_speed\n\n"

        return result
    }

    @RequiresApi(Build.VERSION_CODES.O)
    fun getForecast(weatherJSON: JSONObject): String {
        val list_of_days = weatherJSON.getJSONArray("list")
        var result = ""

        // val dateFormat = SimpleDateFormat("yyyy-MM-dd HH:mm:ss")

        for (i in 0 until 3 * 8) {
            val date_of_forecast = Date(list_of_days.getJSONObject(i).getLong("dt") * 1000)
            val cal = Calendar.getInstance()
            cal.time = date_of_forecast

            if (cal.get(Calendar.HOUR_OF_DAY) == 12) {
                result += cal.get(Calendar.DAY_OF_WEEK).toString() + ", " + cal.get(Calendar.DAY_OF_MONTH).toString() + ":\n" + extractDataFromJSON(list_of_days.getJSONObject(i))
                println(result)
            }
        }

        return result
    }

    @RequiresApi(Build.VERSION_CODES.M)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        MinskInfoLabel = findViewById(R.id.minskInfo)
        SeoulInfoLabel = findViewById(R.id.seoulInfo)
        detailedCityInfoLabel = findViewById<TextView>(R.id.detailedCityInfo)
        inputCityLabel = findViewById(R.id.inputCityNameLabel)

        detailedCityInfoLabel!!.movementMethod = ScrollingMovementMethod()

        requestPermissions(Array(1) { "android.permission.INTERNET" }, 0) // Получаем доступ в интернет
    }
}