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



xBound = c(0,1,0)
yBound = c(0,1,1)
bvd = ComputationalGeometry::BoundedUnweightedVoronoi(coordX = xBound,coordY = yBound,minX = -1,minY = -1,maxX = 2,maxY = 2)
plot(xBound,yBound,pch=16)
for(i in 1:length(bvd$segments)){
  if(any(is.nan(bvd$segments[[i]]))){
    next()
  } else {
    lines(x = c(bvd$segments[[i]][1],bvd$segments[[i]][3]),y = c(bvd$segments[[i]][2],bvd$segments[[i]][4]))
  }
}



bvd = ComputationalGeometry::BoundedUnweightedVoronoi(coordX = x,coordY = y,minX = floor(min(x)),minY = floor(min(y)),maxX = ceiling(max(x)),maxY = ceiling(max(y)))
plot(x,y,pch=16,cex=0.75,xlim=c(-2,80),ylim=c(-2,80))
for(i in 1:length(bvd$segments)){
  if(any(is.nan(bvd$segments[[i]]))){
    next()
  } else {
    lines(x = c(bvd$segments[[i]][1],bvd$segments[[i]][3]),y = c(bvd$segments[[i]][2],bvd$segments[[i]][4]))
  }
}



# weights = rbeta(n = 30,shape1 = 2,shape2 = 5)
weights = rlnorm(n = 30)
bwvd = ComputationalGeometry::BoundedWeightedVoronoi(coordX = x,coordY = y,Weights = weights,minX = floor(min(x)),minY = floor(min(y)),maxX = ceiling(max(x)),maxY = ceiling(max(y)))
plot(x,y,pch=16,cex=0.75,xlim=c(floor(min(x)-1),ceiling(max(x))+1),ylim=c(floor(min(y)-1),ceiling(max(y)+1)))
text(x,y,labels=as.character(round(weights,3)),cex=0.75,adj=c(0.95,0))
for(i in 1:length(bwvd$segments)){
  if(any(is.nan(bwvd$segments[[i]]))){
    next()
  } else {
    lines(x = c(bwvd$segments[[i]][1],bwvd$segments[[i]][3]),y = c(bwvd$segments[[i]][2],bwvd$segments[[i]][4]))
  }
}
