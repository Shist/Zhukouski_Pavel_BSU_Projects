package com.example.pmvs_lab_6_3_3_var_4;
import android.os.Bundle;
import android.view.View;
import android.app.ListActivity;
import android.content.Intent;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;

public class MainActivity extends ListActivity {

    String[] calculators = { "Calculator & Converter" , "Just Converter" };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1, calculators);
        setListAdapter(adapter);
        OnItemClickListener itemListener = new OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View v, int position,
                                    long id) {
                switch (position) {
                    case 0:
                        Intent intent = new Intent(MainActivity.this,
                                TableLayoutCalculator.class);
                        startActivity(intent);
                        break;
                    case 1:
                        Intent intent1 = new
                                Intent(MainActivity.this, FrameLayoutCalculator.class);
                        startActivity(intent1);
                        break;
                }
            }
        };
        getListView().setOnItemClickListener(itemListener);
    }
}