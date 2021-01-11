package com.example.pmvs_lab_10_task_3;

import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private TextView altitudeInfoView;
    private TextView latitudeInfoView;
    private TextView longitudeInfoView;
    private TextView accuracyInfoView;
    private TextView bearingInfoView;

    private static PendingIntent newIntent;

    LocationManager locationManager;
    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        assert data != null;
        Bundle d = data.getExtras();
        Location location = (Location) d.get(LocationManager.KEY_LOCATION_CHANGED);

        altitudeInfoView.setText(String.valueOf(location.getAltitude()));
        latitudeInfoView.setText(String.valueOf(location.getLatitude()));
        longitudeInfoView.setText(String.valueOf(location.getLongitude()));
        accuracyInfoView.setText(String.valueOf(location.getAccuracy()));
        bearingInfoView.setText(String.valueOf(location.getBearing()));
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    public void OnClickStart(View v) {
        if (ContextCompat.checkSelfPermission(
                MainActivity.this, Manifest.permission.ACCESS_FINE_LOCATION) ==
                PackageManager.PERMISSION_GRANTED) {

            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER,
                    0,
                    0.0f,
                    newIntent);

        } else {
            requestPermissions(new String[]{"android.permission.ACCESS_FINE_LOCATION"}, 0);
        }
    }

    public void OnClickEnd(View v) {
        locationManager.removeUpdates(newIntent);
    }

    public void initObjects() {
        altitudeInfoView = findViewById(R.id.AltitudeInfo);
        latitudeInfoView = findViewById(R.id.LatitudeInfo);
        longitudeInfoView = findViewById(R.id.LongitudeInfo);
        accuracyInfoView = findViewById(R.id.AccuracyInfo);
        bearingInfoView = findViewById(R.id.BearingInfo);

        locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);

        newIntent = createPendingResult(0, getIntent(), 0);
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initObjects();
    }
}