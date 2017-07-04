#' Format Output of CGAL Code
#'
#' The readCells(). function reads the file diagram.txt.
#' This is the output file that the external program voronoiDiagram generates.
#' The file contains multiple lines for each vertex (site), so each region (cell) is represented by a block of lines in the file.
#' The blocks are read in the order that the sites were specified in R (by matching the site locations in R to the vertex information in the file), rather than the order that they appear in the file (which may be different).
#' Notice that this function handles two special cases: it is possible that a site location does not appear (as a vertex) in the diagram.txt file at all; it is also possible that a site location appears (as a vertex) in the diagram.txt file, but the file contains no line segments for that vertex.
#' In both cases, a NULL border is returned.
#'
#' @param voronoiOut a list output
#'
#' @export
readCells <- function(voronoiOut){
    diagInfo <- readLines("diagram.txt")
    starts <- grep("^Vertex", diagInfo)
    lengths <- diff(c(starts, length(diagInfo) + 1))
    vertices <- read.table(textConnection(diagInfo[starts]))[-1]
    readCell <- function(start, length) {
        vline <- readLines("diagram.txt", n = start)[start]
        if (length > 1) {
            border <- read.table("diagram.txt", skip = start,
                nrows = length - 1, na.strings = "nan")
        }
        else {
            border <- NULL
        }
        list(vertex = as.numeric(strsplit(vline, " ")[[1]][2:3]),
            border = border)
    }
    result <- vector("list", length(s$x))
    for (i in 1:length(s$x)) {
        sx <- s$x[i]
        sy <- s$y[i]
        eps <- 0.01
        match <- which((abs(sx - vertices[, 1]) < eps) & (abs(sy -
            vertices[, 2]) < eps))
        if (length(match)) {
            result[[i]] <- readCell(starts[match], lengths[match])
        }
        else {
            result[[i]] <- list(vertex = c(sx, sy), border = NULL)
        }
    }
    result
}
