package com.example.pmvs_lab_10_task_2;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.example.pmvs_lab_10_task_2.R;

public class MainActivity extends AppCompatActivity {

    private TextView altitudeInfoView;
    private TextView latitudeInfoView;
    private TextView longitudeInfoView;

    LocationManager locationManager;
    LocationListener locationListener;

    @RequiresApi(api = Build.VERSION_CODES.M)
    public void OnClickStart(View v) {
        if (ContextCompat.checkSelfPermission(
                MainActivity.this, Manifest.permission.ACCESS_FINE_LOCATION) ==
                PackageManager.PERMISSION_GRANTED) {
            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0.0f, locationListener);

        } else {
            requestPermissions(new String[]{"android.permission.ACCESS_FINE_LOCATION"}, 0);
        }
    }

    public void OnClickEnd(View v) {
        locationManager.removeUpdates(locationListener);
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        locationManager = (LocationManager)
                getSystemService(Context.LOCATION_SERVICE);

        // requestPermissions(new String[]{"android.permission.ACCESS_FINE_LOCATION"}, 0);

        altitudeInfoView = findViewById(R.id.AltitudeInfo);
        latitudeInfoView = findViewById(R.id.LatitudeInfo);
        longitudeInfoView = findViewById(R.id.LongitudeInfo);

        if (ContextCompat.checkSelfPermission(
                MainActivity.this, Manifest.permission.ACCESS_FINE_LOCATION) ==
                PackageManager.PERMISSION_GRANTED) {
            Toast.makeText(getApplicationContext(), "Прав достаточно", Toast.LENGTH_SHORT).show();
        } else {
            requestPermissions(new String[]{"android.permission.ACCESS_FINE_LOCATION"}, 0);
        }

        locationListener = location -> {
            altitudeInfoView.setText(String.valueOf(location.getAltitude()));
            latitudeInfoView.setText(String.valueOf(location.getLatitude()));
            longitudeInfoView.setText(String.valueOf(location.getLongitude()));
        };

    }
}