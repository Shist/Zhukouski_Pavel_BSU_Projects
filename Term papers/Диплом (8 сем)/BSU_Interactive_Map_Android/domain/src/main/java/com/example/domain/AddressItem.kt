package com.example.domain

import android.os.Parcel
import android.os.Parcelable

// This is domain data class. Actually this is copy of corresponding AddressItemDB, but we
// need it in order to hide the database implementation logic. It is considered good practice
// to have separate classes for the database and classes for the domain.
data class AddressItem(

    val id: String,

    val description: String?,

    val latitude: String?,

    val longitude: String?

) : Parcelable { // We need to implement an interface Parcelable in order to save this object in Bundle (for example, while rotating phone)
    constructor(parcel: Parcel) : this(
        parcel.readString()!!,
        parcel.readString(),
        parcel.readString(),
        parcel.readString()
    ) {
    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        parcel.writeString(id)
        parcel.writeString(description)
        parcel.writeString(latitude)
        parcel.writeString(longitude)
    }

    override fun describeContents(): Int {
        return 0
    }

    companion object CREATOR : Parcelable.Creator<AddressItem> {
        override fun createFromParcel(parcel: Parcel): AddressItem {
            return AddressItem(parcel)
        }

        override fun newArray(size: Int): Array<AddressItem?> {
            return arrayOfNulls(size)
        }
    }
}