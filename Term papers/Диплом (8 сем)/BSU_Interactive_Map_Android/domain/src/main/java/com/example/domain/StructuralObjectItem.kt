package com.example.domain

import android.os.Parcel
import android.os.Parcelable

// This is domain data class. Actually this is copy of corresponding StructuralObjectItemDB, but we
// need it in order to hide the database implementation logic. It is considered good practice
// to have separate classes for the database and classes for the domain.
data class StructuralObjectItem(

    val id: String,

    val subdivision: String?,

    val description: String?,

    val website: String?,

    val buildingId: String?,

    val category: String?,

    val icon: IconItem?,

) : Parcelable { // We need to implement an interface Parcelable in order to save this object in Bundle (for example, while rotating phone)
    constructor(parcel: Parcel) : this(
        parcel.readString()!!,
        parcel.readString(),
        parcel.readString(),
        parcel.readString(),
        parcel.readString(),
        parcel.readString(),
        parcel.readParcelable(IconItem::class.java.classLoader)
    ) {
    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        parcel.writeString(id)
        parcel.writeString(subdivision)
        parcel.writeString(description)
        parcel.writeString(website)
        parcel.writeString(buildingId)
        parcel.writeString(category)
        parcel.writeParcelable(icon, flags)
    }

    override fun describeContents(): Int {
        return 0
    }

    companion object CREATOR : Parcelable.Creator<StructuralObjectItem> {
        override fun createFromParcel(parcel: Parcel): StructuralObjectItem {
            return StructuralObjectItem(parcel)
        }

        override fun newArray(size: Int): Array<StructuralObjectItem?> {
            return arrayOfNulls(size)
        }
    }
}