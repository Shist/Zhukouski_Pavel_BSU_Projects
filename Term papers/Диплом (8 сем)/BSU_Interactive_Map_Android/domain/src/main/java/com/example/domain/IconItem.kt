package com.example.domain

import android.os.Parcel
import android.os.Parcelable

// This is domain data class. Actually this is copy of corresponding IconItemDB, but we
// need it in order to hide the database implementation logic. It is considered good practice
// to have separate classes for the database and classes for the domain.
data class IconItem(

    val id: String,

    val subdivision: String?,

    val logoPath: String?

) : Parcelable { // We need to implement an interface Parcelable in order to save this object in Bundle (for example, while rotating phone)
    constructor(parcel: Parcel) : this(
        parcel.readString()!!,
        parcel.readString(),
        parcel.readString()
    ) {
    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        parcel.writeString(id)
        parcel.writeString(subdivision)
        parcel.writeString(logoPath)
    }

    override fun describeContents(): Int {
        return 0
    }

    companion object CREATOR : Parcelable.Creator<IconItem> {
        override fun createFromParcel(parcel: Parcel): IconItem {
            return IconItem(parcel)
        }

        override fun newArray(size: Int): Array<IconItem?> {
            return arrayOfNulls(size)
        }
    }
}