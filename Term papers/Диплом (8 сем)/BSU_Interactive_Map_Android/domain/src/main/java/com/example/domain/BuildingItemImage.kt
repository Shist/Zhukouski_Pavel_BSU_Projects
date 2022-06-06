package com.example.domain

import android.os.Parcel
import android.os.Parcelable

// This is domain data class. Actually this is copy of corresponding BuildingItemImageDB, but we
// need it in order to hide the database implementation logic. It is considered good practice
// to have separate classes for the database and classes for the domain.
data class BuildingItemImage(

    val buildingId: String,

    val description: String?,

    val imagePath: String?

) : Parcelable { // We need to implement an interface Parcelable in order to save this object in Bundle (for example, while rotating phone)
    constructor(parcel: Parcel) : this(
        parcel.readString()!!,
        parcel.readString(),
        parcel.readString(),
    ) {
    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        parcel.writeString(buildingId)
        parcel.writeString(description)
        parcel.writeString(imagePath)
    }

    override fun describeContents(): Int {
        return 0
    }

    companion object CREATOR : Parcelable.Creator<BuildingItemImage> {
        override fun createFromParcel(parcel: Parcel): BuildingItemImage {
            return BuildingItemImage(parcel)
        }

        override fun newArray(size: Int): Array<BuildingItemImage?> {
            return arrayOfNulls(size)
        }
    }
}