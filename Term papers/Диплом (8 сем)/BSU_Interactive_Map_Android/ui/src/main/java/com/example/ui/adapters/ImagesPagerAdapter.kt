package com.example.ui.adapters

import android.text.Html
import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.TextView
import android.widget.ImageView
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.domain.BuildingItemImage
import com.example.ui.databinding.ImgPagerItemBinding
import com.squareup.picasso.Picasso

// This class is needed to place image objects (consist of image and description) into ViewPager
class ImagesPagerAdapter(private val isModern: Boolean) :
    ListAdapter<BuildingItemImage, ImagesPagerAdapter.ItemViewHolder>(ImageObjectsDiffCallback()) {

    class ItemViewHolder(itemBinding: ImgPagerItemBinding) :
        RecyclerView.ViewHolder(itemBinding.root) {

        val image: ImageView
        val imgDescription: TextView

        init {
            image = itemBinding.pagerImg
            imgDescription = itemBinding.info
        }
    }

    override fun onBindViewHolder(holder: ItemViewHolder, position: Int) {
        val imageObject = getItem(position)
        if (isModern) {
            Picasso.get().load("http://map.bsu.by/buildings_images/modern_buildings/" +
                    imageObject.imagePath).into(holder.image)
        } else {
            Picasso.get().load("http://map.bsu.by/buildings_images/historical_buildings/" +
                    imageObject.imagePath).into(holder.image)
        }
        holder.imgDescription.text = Html.fromHtml(imageObject.description, Html.FROM_HTML_MODE_LEGACY).toString()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ItemViewHolder {
        return ItemViewHolder(ImgPagerItemBinding.inflate(LayoutInflater.from(parent.context), parent, false))
    }

}

class ImageObjectsDiffCallback : DiffUtil.ItemCallback<BuildingItemImage>() {
    override fun areItemsTheSame(oldItem: BuildingItemImage, newItem: BuildingItemImage): Boolean {
        return oldItem.imagePath == newItem.imagePath
    }

    override fun areContentsTheSame(oldItem: BuildingItemImage, newItem: BuildingItemImage): Boolean {
        return oldItem == newItem
    }
}