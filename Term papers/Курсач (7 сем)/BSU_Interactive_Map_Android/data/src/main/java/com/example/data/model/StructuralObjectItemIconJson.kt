package com.example.data.model

import com.google.gson.annotations.SerializedName

data class StructuralObjectItemIconJson(
    @SerializedName("structuralObjectId") var structuralObjectId: String?,
    @SerializedName("subdivision") var subdivision: String?,
    @SerializedName("logoPath") var logoPath: String?
)
