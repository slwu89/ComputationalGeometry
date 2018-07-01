#######################################
#
# Sean Wu & Yuji Saikai
# Tests for ComputationalGeometry
# July 1, 2017
#
#######################################

library(ComputationalGeometry)
library(viridisLite)
library(viridis)


#######################################
# Unweighted Voronoi Tests
#######################################

x = runif(n = 30,min = 0,max = 50)
y = runif(n = 30,min = 0,max = 50)

wvd = ComputationalGeometry::UnboundedUnweightedVoronoi(coordX = x,coordY = y)
plot(x,y,pch=16,cex=0.75,xlim=c(-2,50),ylim=c(-2,50))
for(i in 1:length(wvd$boundedFaceEdges)){
  lines(x = c(wvd$boundedFaceEdges[[i]][1],wvd$boundedFaceEdges[[i]][3]),y = c(wvd$boundedFaceEdges[[i]][2],wvd$boundedFaceEdges[[i]][4]))
}
for(i in 1:length(wvd$unboundedEdges)){
  points(x = wvd$unboundedEdges[[i]][1],y = wvd$unboundedEdges[[i]][2],pch=16,col="red",cex=0.75)
}

# bounded unweighted voronoi
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

# bounded unweighted voronoi
bvd = ComputationalGeometry::BoundedUnweightedVoronoi(coordX = x,coordY = y,minX = floor(min(x)),minY = floor(min(y)),maxX = ceiling(max(x)),maxY = ceiling(max(y)))
plot(x,y,pch=16,cex=0.75,xlim=c(0,50),ylim=c(0,50))
for(i in 1:length(bvd$segments)){
  if(any(is.nan(bvd$segments[[i]]))){
    next()
  } else {
    lines(x = c(bvd$segments[[i]][1],bvd$segments[[i]][3]),y = c(bvd$segments[[i]][2],bvd$segments[[i]][4]))
  }
}


#######################################
# Weighted Voronoi Tests
#######################################

nPts = 50
x = runif(n = nPts,min = 0,max = 100)
y = runif(n = nPts,min = 0,max = 100)
minX = min(x)-10
minY = min(y)-10
maxX = max(x)+10
maxY = max(y)+10
weights = rlnorm(n = nPts,mean = 0,sd = 1)

voronoiGaussian = ComputationalGeometry::BoundedWeightedVoronoi(coordX = x,coordY = y,Weights = weights,
                                                            minX = minX,minY = minY,
                                                            maxX = maxX,maxY = maxY)

plot(x,y,pch=16,cex=0.75,xlim=c(minX,maxX),ylim=c(minY,maxY),
     col = viridis(length(weights),option = "D",end = 0.7)[factor(weights)],main = "Log-Gaussian distributed weights")
text(x,y,labels = round(weights,2),col = viridis(length(weights),option = "D",end = 0.7)[factor(weights)],pos = 1)
for(i in 1:length(voronoiGaussian$segments)){
  if(any(is.nan(voronoiGaussian$segments[[i]]))){
    # points(x = c(voronoiGaussian$segments[[i]][1],voronoiGaussian$segments[[i]][2]),pch=16,cex=0.75,col="black")
    next()
  } else {
    lines(x = c(voronoiGaussian$segments[[i]][1],voronoiGaussian$segments[[i]][3]),
          y = c(voronoiGaussian$segments[[i]][2],voronoiGaussian$segments[[i]][4]))
  }
}


nPts = 1000
x = runif(n = nPts,min = 0,max = 100)
y = runif(n = nPts,min = 0,max = 100)
minX = min(x)-0.01
minY = min(y)-0.01
maxX = max(x)+0.01
maxY = max(y)+0.01
weightsBeta = rbeta(n = nPts,shape1 = 0.25,shape2 = 0.25)
weightsLogNorm = rlnorm(n = nPts)
weightsExp = rexp(n = nPts)
weightsSame = rep(x = 1,times = nPts)
voronoiBeta = ComputationalGeometry::BoundedWeightedVoronoi(coordX = x,coordY = y,Weights = weightsBeta,
                                                            minX = minX,minY = minY,
                                                            maxX = maxX,maxY = maxY)
voronoiLogNorm = ComputationalGeometry::BoundedWeightedVoronoi(coordX = x,coordY = y,Weights = weightsLogNorm,
                                                            minX = minX,minY = minY,
                                                            maxX = maxX,maxY = maxY)
voronoiExp = ComputationalGeometry::BoundedWeightedVoronoi(coordX = x,coordY = y,Weights = weightsExp,
                                                               minX = minX,minY = minY,
                                                               maxX = maxX,maxY = maxY)
voronoiSame = ComputationalGeometry::BoundedWeightedVoronoi(coordX = x,coordY = y,Weights = weightsSame,
                                                            minX = minX,minY = minY,
                                                            maxX = maxX,maxY = maxY)
# plot
par(mfrow=c(2,2))

plot(x,y,pch=16,cex=0.75,xlim=c(minX,maxX),ylim=c(minY,maxY),
     col = viridis(length(weightsBeta),option = "D")[rev(rank(weightsBeta))],main = "Beta-distributed Weights")
for(i in 1:length(voronoiBeta$segments)){
  if(any(is.nan(voronoiBeta$segments[[i]]))){
    next()
  } else {
    lines(x = c(voronoiBeta$segments[[i]][1],voronoiBeta$segments[[i]][3]),y = c(voronoiBeta$segments[[i]][2],voronoiBeta$segments[[i]][4]))
  }
}

plot(x,y,pch=16,cex=0.75,xlim=c(minX,maxX),ylim=c(minY,maxY),
     col = viridis(length(weightsLogNorm),option = "D")[rev(rank(weightsLogNorm))],main = "Log Normal-distributed Weights")
for(i in 1:length(voronoiLogNorm$segments)){
  if(any(is.nan(voronoiLogNorm$segments[[i]]))){
    next()
  } else {
    lines(x = c(voronoiLogNorm$segments[[i]][1],voronoiLogNorm$segments[[i]][3]),y = c(voronoiLogNorm$segments[[i]][2],voronoiLogNorm$segments[[i]][4]))
  }
}

plot(x,y,pch=16,cex=0.75,xlim=c(minX,maxX),ylim=c(minY,maxY),
     col = viridis(length(weightsExp),option = "D")[rev(rank(weightsExp))],main = "Exponentially-distributed Weights")
for(i in 1:length(voronoiExp$segments)){
  if(any(is.nan(voronoiExp$segments[[i]]))){
    next()
  } else {
    lines(x = c(voronoiExp$segments[[i]][1],voronoiExp$segments[[i]][3]),y = c(voronoiExp$segments[[i]][2],voronoiExp$segments[[i]][4]))
  }
}

plot(x,y,pch=16,cex=0.75,xlim=c(minX,maxX),ylim=c(minY,maxY),
     col = viridis(length(weightsSame),option = "D")[rev(rank(weightsSame))],main = "Unweighted")
for(i in 1:length(voronoiSame$segments)){
  if(any(is.nan(voronoiSame$segments[[i]]))){
    next()
  } else {
    lines(x = c(voronoiSame$segments[[i]][1],voronoiSame$segments[[i]][3]),y = c(voronoiSame$segments[[i]][2],voronoiSame$segments[[i]][4]))
  }
}

par(mfrow=c(1,1))
