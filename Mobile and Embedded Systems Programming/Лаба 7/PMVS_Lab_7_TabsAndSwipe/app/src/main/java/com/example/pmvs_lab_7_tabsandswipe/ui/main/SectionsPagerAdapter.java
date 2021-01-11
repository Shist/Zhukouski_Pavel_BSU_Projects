package com.example.pmvs_lab_7_tabsandswipe.ui.main;

import android.content.Context;
import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.annotation.StringRes;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import com.example.pmvs_lab_7_tabsandswipe.R;

/**
 * A [FragmentPagerAdapter] that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */
public class SectionsPagerAdapter extends FragmentPagerAdapter {

    @StringRes
    private static final int[] TAB_TITLES = new int[]{R.string.title_section1, R.string.title_section2, R.string.title_section3};
    private final Context mContext;

    public SectionsPagerAdapter(Context context, FragmentManager fm) {
        super(fm);
        mContext = context;
    }

    @Override
    public Fragment getItem(int position) {
// getItem is called to instantiate the fragment for the given page.
// Return a DummySectionFragment (defined as a static inner class
// below) with the page number as its lone argument.
        Fragment fragment=null;
        Bundle args;
        switch (position) {
            case 0:
                fragment = new FirstFragment();
                args = new Bundle();
                args.putInt(FirstFragment.ARG_SECTION_NUMBER, position + 1);
                fragment.setArguments(args);
                break;
            case 1:
                fragment = new SecondFragment();
                args = new Bundle();
                args.putInt(SecondFragment.ARG_SECTION_NUMBER, position +
                        1);
                fragment.setArguments(args);
                break;
            case 2:
                fragment = new ThirdFragment();
                args = new Bundle();
                args.putInt(ThirdFragment.ARG_SECTION_NUMBER, position + 1);
                fragment.setArguments(args);
                break;
        }
        return fragment;
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        return mContext.getResources().getString(TAB_TITLES[position]);
    }

    @Override
    public int getCount() {
        return 3;
    }
}