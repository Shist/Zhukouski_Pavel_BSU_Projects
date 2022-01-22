package com.example.domain

data class IconItem(

    val id: String,

    val subdivision: String?,

    val logoPath: String?

)

// This is domain data class. Actually this is copy of corresponding IconItemDB, but we
// need it in order to hide the database implementation logic. It is considered good practice
// to have separate classes for the database and classes for the domain.
