package com.example.pmvs_lab_7_tabsandswipe.ui.main;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;

import com.example.pmvs_lab_7_tabsandswipe.R;

/**
 * A placeholder fragment containing a simple view.
 */
public class FirstFragment extends Fragment {

    public static final String ARG_SECTION_NUMBER = "section_number";

    private PageViewModel pageViewModel;

    public static FirstFragment newInstance(int index) {
        FirstFragment fragment = new FirstFragment();
        Bundle bundle = new Bundle();
        bundle.putInt(ARG_SECTION_NUMBER, index);
        fragment.setArguments(bundle);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        pageViewModel = new ViewModelProvider(this).get(PageViewModel.class);
        int index = 1;
        if (getArguments() != null) {
            index = getArguments().getInt(ARG_SECTION_NUMBER);
        }
        pageViewModel.setIndex(index);
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.first_tab, container,
                false);
        TextView dummyTextView = (TextView) rootView.findViewById(R.id.textView1);
        pageViewModel.getText().observe(this, new Observer<String>() {
            @Override
            public void onChanged(@Nullable String s) {
                dummyTextView.setText((dummyTextView.getText() + ". " + s + "."));
            }
        });
        return rootView;
    }
}