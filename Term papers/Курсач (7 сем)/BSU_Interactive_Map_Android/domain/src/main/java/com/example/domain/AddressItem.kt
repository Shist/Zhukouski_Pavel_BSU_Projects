package com.example.domain

data class AddressItem(

    val id: String,

    val description: String?,

    val latitude: String?,

    val longitude: String?

)

// This is domain data class. Actually this is copy of corresponding AddressItemDB, but we
// need it in order to hide the database implementation logic. It is considered good practice
// to have separate classes for the database and classes for the domain.
