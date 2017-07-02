#######################################
#
# Sean Wu
#
#######################################

library(ComputationalGeometry)

x = runif(n = 30,min = 0,max = 50)
y = runif(n = 30,min = 0,max = 50)
# weights = rlnorm(n = 30)
weights = rep(0,times=30)

wvd = ComputationalGeometry::WeightedVoronoi(coordX = x,coordY = y,Weights = weights)

plot(x,y,pch=16,cex=0.75,xlim=c(-2,50),ylim=c(-2,50))
for(i in 1:length(wvd$x)){
  polygon(x = wvd$x[[i]],y = wvd$y[[i]])
}

for(j in 1:length(wvd$hyperbolaSources)){
  lines(x = c(wvd$hyperbolaSources[[j]]$sourceX,wvd$hyperbolaSources[[j]]$sourceY),
        y = c(wvd$hyperbolaTargets[[j]]$sourceX,wvd$hyperbolaTargets[[j]]$sourceY),
        col = "steelblue")
}

xBound = c(0,1,0)
yBound = c(0,1,1)
bvd = ComputationalGeometry::BoundedUnweightedVoronoi(coordX = xBound,coordY = yBound,minX = -1,minY = -1,maxX = 2,maxY = 2)
