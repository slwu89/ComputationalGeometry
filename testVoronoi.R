#######################################
#
# Sean Wu
#
#######################################

library(ComputationalGeometry)

x = runif(n = 20)
y = runif(n = 20)
weights = runif(n = 20)

wvd = ComputationalGeometry::WeightedVoronoi(coordX = x,coordY = y,Weights = weights)

plot(x,y,pch=16,cex=0.75)
for(i in 1:length(wvd$x)){
  polygon(x = wvd$x[[i]],y = wvd$y[[i]])
}
