#The code below could be used to build a red-green map based on the dataset.
	
url = "https://raw.githubusercontent.com/SimonDuGL/driver/main/us_map.json";
gdf = gpd.read_file(url)
gdf.crs = 'epsg:4326'
gplt.polyplot(gdf, figsize=(20, 4));

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
