#The code below could be used to build a red-green map based on the dataset.
	
url = "https://raw.githubusercontent.com/SimonDuGL/driver/main/us_map.json";
gdf = gpd.read_file(url)
gdf.crs = 'epsg:4326'
gplt.polyplot(gdf, figsize=(20, 4));

![map](https://user-images.githubusercontent.com/101145370/165690547-fff034f0-6470-4dbf-89f5-9f1015746906.png)

gplt.choropleth(
    gdf, hue="Median_PriceToRentRatio_AllHomes", edgecolor='white', linewidth=1,
    cmap="PiYG_r", legend=True, figsize=(50, 20))
#gplt.plot(
#    column="Median_PriceToRentRatio_AllHomes",
#    legend=True,
#    scheme="quantiles",
#    figsize=(15, 10),
#    missing_kwds={
#        "color": "lightgrey",
#        "edgecolor": "red",
#        "hatch": "///",
#        "label": "Missing values",
#    },
#);
![map002](https://user-images.githubusercontent.com/101145370/165690621-7db77feb-b04a-4219-a735-79d00354bdcc.png)

