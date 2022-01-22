package com.example.data.model

import com.google.gson.annotations.SerializedName

data class BuildingItemAddressCoordinatesJson(
    @SerializedName("latitude") var latitude: String?,
    @SerializedName("longitude") var longitude: String?
)
