## ----setup, include = FALSE---------------------------------------------------
# knitr::opts_chunk$set(
#   collapse = TRUE,
#   comment = "#>"
# )
knitr::opts_chunk$set(echo = TRUE, warning=FALSE, message=FALSE, fig.cap = " ", fig.path='figs/')

## -----------------------------------------------------------------------------
# install.packages("sandwich")
library("sandwich")

## -----------------------------------------------------------------------------
hs.sampling = load.shp("./data", "hs.sampling.shapefile")
hs.ssh = load.shp("./data", "hs.ssh.shapefile")
# here's another candidate SSH layer
hs.ssh2 = load.shp("./data", "hs.ssh2.shapefile")
hs.reporting = load.shp("./data", "hs.reporting.shapefile")

## ----fig.align="center", fig.width=4, fig.height=3----------------------------
# sampling layer
ggplot(data=hs.sampling) + geom_sf(aes(color=Population))
# SSH layer
ggplot(data=hs.ssh) + geom_sf(aes(fill=STR_1)) + labs(fill='Strata 1')
# another SSH layer
ggplot(data=hs.ssh2) + geom_sf(aes(fill=STR_2)) + labs(fill='Strata 2')
# reporting layer
ggplot(data=hs.reporting) + geom_sf(aes(fill=CODE))

## -----------------------------------------------------------------------------
hs.join = geodetector.data(hs.sampling, hs.ssh, "STR_1")
hs.join = geodetector.data(hs.join, hs.ssh2, "STR_2")
hs.join

## -----------------------------------------------------------------------------
geodetector.factor(hs.join, "Population", c("STR_1", "STR_2"))

## -----------------------------------------------------------------------------
geodetector.interaction(hs.join, "Population", c("STR_1", "STR_2"))

## -----------------------------------------------------------------------------
hs.sw = sandwich.model(hs.sampling, hs.ssh, hs.reporting, "Population")
hs.sw

## ----fig.align="center", fig.width=4, fig.height=3----------------------------
# mean
plot.mean(hs.sw)
# standard error
plot.se(hs.sw)

## -----------------------------------------------------------------------------
hs.sw.con = sandwich.confint(hs.sw, level=.95)

## ----fig.align="center", fig.width=8, fig.height=3----------------------------
plot.ci(hs.sw.con)

## -----------------------------------------------------------------------------
hs.cv = sandwich.cv(hs.sampling, hs.ssh, hs.reporting, "Population", k=5)
hs.cv

