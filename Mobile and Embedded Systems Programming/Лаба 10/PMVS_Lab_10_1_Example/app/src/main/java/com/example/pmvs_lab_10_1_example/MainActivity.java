package com.example.pmvs_lab_10_1_example;

import android.Manifest;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.widget.TextView;

import androidx.core.app.ActivityCompat;

public class MainActivity extends Activity {
    TextView tvOut;
    TextView tvLon;
    TextView tvLat;

    int num = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tvOut = (TextView) findViewById(R.id.textView1);
        tvLon = (TextView) findViewById(R.id.textView2);
        tvLat = (TextView) findViewById(R.id.textView3);
        //Получаем сервис
        LocationManager mlocManager = (LocationManager)
                getSystemService(Context.LOCATION_SERVICE);
        LocationListener mlocListener = new LocationListener() {
            public void onLocationChanged(Location location) {
            //Called when a new location is found by the network location provider.
                tvLat.append(" " + location.getLatitude());
                tvLon.append(" " + location.getLongitude());
                num++;
                System.out.println(num);
            }

            public void onStatusChanged(String provider, int status, Bundle extras) {
            }

            public void onProviderEnabled(String provider) {
            }

            public void onProviderDisabled(String provider) {
            }
        };
        //Подписываемся на изменения в показаниях датчика
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return;
        }
        mlocManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0,
                mlocListener);
        //Если gps включен, то ... , иначе вывести "GPS is not turned on..."
        if (mlocManager.isProviderEnabled(LocationManager.GPS_PROVIDER)) {
            tvOut.setText(R.string.GPS_on);
        } else {
            tvOut.setText(R.string.GPS_off);
        }
    }
}