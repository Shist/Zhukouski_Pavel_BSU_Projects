package app.technobearproject

import android.os.Parcel
import android.os.Parcelable
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.saveable.Saver
import androidx.compose.runtime.saveable.SaverScope

enum class ProductType {
    PHONE,
    TV,
    JOYSTICK,
    KEYBOARD,
    HEADPHONE,
    NOTEBOOK,
    PC,
    NONE
}

class ProductItem(val name: String = "",
                  val price: String = "",
                  val image: Int = 0,
                  val description: String = "",
                  val type: ProductType = ProductType.NONE,
                  var selectedAmount: MutableState<String> = mutableStateOf("0"),
                  var basketAmount: MutableState<String> = mutableStateOf("0")) : Parcelable {
    constructor(parcel: Parcel) : this(
        parcel.readString()!!,
        parcel.readString()!!,
        parcel.readInt(),
        parcel.readString()!!,
        ProductType.valueOf(parcel.readString()!!),
        mutableStateOf(parcel.readString()!!),
        mutableStateOf(parcel.readString()!!)
    ) {
    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        parcel.writeString(name)
        parcel.writeString(price)
        parcel.writeInt(image)
        parcel.writeString(description)
        parcel.writeString(this.type.name)
        parcel.writeString(this.selectedAmount.value)
        parcel.writeString(this.basketAmount.value)
    }

    override fun describeContents() = 0

    companion object CREATOR : Parcelable.Creator<ProductItem> {
        override fun createFromParcel(parcel: Parcel): ProductItem {
            return ProductItem(parcel)
        }

        override fun newArray(size: Int): Array<ProductItem?> {
            return arrayOfNulls(size)
        }
    }
}

val itemsWholeList = listOf(
    ProductItem("DualSense Wireless Controller ",
        "\$209.99",
        R.drawable.cfi_zct1w_besprovodnoy_kontroller_dualsense_ps5_1_600,
        "Main characteristics\n" +
                "Type: Gamepad\n" +
                "Compatibility: Sony PlayStation 5\n" +
                "Interface: USB, Bluetooth ",
        ProductType.JOYSTICK,
        mutableStateOf("0"),
        mutableStateOf("0")),
    ProductItem("HyperX Cloud Stinger Core PC Headset (HX-HSCSC2-BK / WW) ",
        "\$127.00",
        R.drawable.hx_hscsc2_bk_ww_cloud_stinger_core_hyperx_1_600,
        "Main characteristics\n" +
                "Device type: Headphones with microphone\n" +
                "Connection type: Wired\n" +
                "Max. cable length (reach): 3 m\n" +
                "Headphone Construction: Monitor\n" +
                "Headphone acoustic design: Closed ",
        ProductType.HEADPHONE,
        mutableStateOf("0"),
        mutableStateOf("0")),
    ProductItem("Keyboard Defender Mayhem GK-360DL ",
        "\$25.00",
        R.drawable.good_img_a0538f1f_a2e3_11e9_80c7_005056840c70_600,
        "Main characteristics\n" +
                "Keyboard type: Gaming\n" +
                "Keyboard Connection Type: Wired\n" +
                "Keyboard connection interface: USB\n" +
                "Switch Technology: Membrane\n" +
                "Key Illumination: Yes ",
        ProductType.KEYBOARD,
        mutableStateOf("0"),
        mutableStateOf("0")),
    ProductItem("Honor MagicBook X14 NBR-WAI9 Notebook ",
        "\$1625.00",
        R.drawable.nbr_wai9_magicbook_x14_space_gray_noutbuk_honor_1_600,
        "Main characteristics\n" +
                "Screen: 14.0 \"1920x1080 p, IPS 60 Hz, 250 cd / m2\n" +
                "Processor: Intel Core-i3 10110U 2-core, 2.1 GHz - 4.1 GHz, Comet Lake\n" +
                "Graphics: Integrated Intel UHD Graphics 620\n" +
                "Memory: 8GB DDR4 RAM, 256GB SSD\n" +
                "Operating system version: Windows 10\n" +
                "Weight and dimensions: 1.4 kg, 322 mm x 215 mm x 16 mm ",
        ProductType.NOTEBOOK,
        mutableStateOf("0"),
        mutableStateOf("0")),
    ProductItem("Monoblock Lenovo IdeaCentre AIO 3 22ITL6 F0G5001ARK ",
        "\$1701.00",
        R.drawable.a22itl6_f0g5001ark_ideacentre_aio_3_monoblok_lenovo_1_600,
        "Main characteristics\n" +
                "Screen: 1920x1080 pixels, WVA\n" +
                "Processor: Intel Pentium Gold 7505 2-core, 2.0 GHz - 3.5 GHz\n" +
                "Graphics: Integrated Intel UHD Graphics\n" +
                "Memory: 8GB DDR4 RAM, 256GB SSD\n" +
                "Package contents: Power adapter, Documentation, Keyboard, Mouse ",
        ProductType.PC,
        mutableStateOf("0"),
        mutableStateOf("0")),
    ProductItem("Smartphone SAMSUNG Galaxy A22 4GB / 128GB (white)",
        "\$599.99",
        R.drawable.galaxya22128gbsma225fzkgser_samsung_60f6e745471be,
        "Type: smartphone\n" +
                "Screen diagonal: 6.4″ \n" +
                "Control type: touch\n" +
                "Number of SIM-cards: 2\n" +
                "SIM-card format: Nano-SIM\n" +
                "Operating system: Android\n" +
                "Operating system version: Android 11.0\n" +
                "Branded graphical interface: One UI\n" +
                "Product Range: Galaxy A22 (Samsung)\n" +
                "Certification: PCT / STB / EAC",
        ProductType.PHONE,
        mutableStateOf("0"),
        mutableStateOf("0")),
    ProductItem("Samsung TV QE55Q67AAUXRU",
        "\$2484.00",
        R.drawable.qe43q60aauxru_samsung_607d5ce61da8f,
        "Type: QLED\n" +
                "Series: 6\n" +
                "Screen dimensions: 43 \"\n" +
                "Permission: 3,840 x 2,160\n" +
                "Screen curvature: No\n" +
                "Anti Reflection: No\n" +
                "HDMI connector: 3\n" +
                "USB: 2 ",
        ProductType.TV,
        mutableStateOf("0"),
        mutableStateOf("0"))
)