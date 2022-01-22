package com.example.ui.fragments

import android.app.Activity
import android.app.Dialog
import android.content.Context
import android.graphics.Color
import android.graphics.Point
import org.osmdroid.api.IMapView
import android.widget.TextView
import android.graphics.drawable.ColorDrawable
import org.osmdroid.views.overlay.OverlayItem
import android.graphics.drawable.Drawable
import android.util.Log
import android.view.Gravity
import org.osmdroid.views.MapView
import android.view.Window
import android.widget.ImageView
import com.example.ui.R

import org.osmdroid.views.overlay.ItemizedOverlay


class MapItemizedOverlay(defaultMarker: Drawable?, context: Context) :
    ItemizedOverlay<OverlayItem>(defaultMarker) {

    private val mOverlays = ArrayList<OverlayItem>()
    private val mContext: Context = context

    fun addOverlay(overlay: OverlayItem) {
        mOverlays.add(overlay)
        populate()
    }

    override fun createItem(i: Int): OverlayItem {
        return mOverlays[i]
    }

    override fun size(): Int {
        return mOverlays.size
    }

    override fun onTap(index: Int): Boolean {
        val item = mOverlays[index]

        val map = (mContext as Activity).findViewById<MapView>(R.id.map)
        map.controller.setCenter(mOverlays[index].point)

        //set up dialog
        val dialog = Dialog(mContext)
        dialog.window?.setGravity(Gravity.CENTER)
        dialog.window?.requestFeature(Window.FEATURE_NO_TITLE)
        dialog.window?.setBackgroundDrawable(ColorDrawable(Color.TRANSPARENT))
        dialog.setContentView(R.layout.custom_dialog)
        //dialog.setTitle("This is my custom dialog box");
        dialog.setCancelable(true)
        //there are a lot of settings, for dialog, check them all out!

        //set up text
        val mapPopupHeader = dialog.findViewById(R.id.map_popup_header) as TextView
        mapPopupHeader.text = item.title
        val mapPopupBody = dialog.findViewById(R.id.map_popup_body) as TextView
        mapPopupBody.text = item.snippet

        //set up button
        val imgMoreInfo: ImageView = dialog.findViewById(R.id.map_more_info_imageView) as ImageView
        imgMoreInfo.setOnClickListener { Log.d("Clicked", "more info") }

        //now that the dialog is set up, it's time to show it
        dialog.show()
        return true
    }

    override fun onSnapToItem(arg0: Int, arg1: Int, arg2: Point?, arg3: IMapView?): Boolean {
        return false
    }

}