package com.example.data.model

import com.google.gson.annotations.SerializedName

data class BuildingItemTypeJson(
    @SerializedName("type") var type: String?,
    @SerializedName("markerPath") var markerPath: String?
)