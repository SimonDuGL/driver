#The demonstation of building a friendly red-green map based on the dataset.
#The code is shown below:
	
url = "https://raw.githubusercontent.com/SimonDuGL/driver/main/us_map.json";

gdf = gpd.read_file(url);

gdf.crs = 'epsg:4326';

gplt.polyplot(gdf, figsize=(20, 4));

gplt.choropleth(
    gdf, hue="Median_PriceToRentRatio_AllHomes", edgecolor='white', linewidth=1,
    cmap="PiYG_r", legend=True, figsize=(50, 20))

![map002](https://user-images.githubusercontent.com/101145370/165690621-7db77feb-b04a-4219-a735-79d00354bdcc.png)

