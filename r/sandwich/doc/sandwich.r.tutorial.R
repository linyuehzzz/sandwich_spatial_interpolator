## ----setup, include = FALSE---------------------------------------------------
knitr::opts_chunk$set(echo = TRUE, warning=FALSE, message=FALSE, fig.cap = " ", fig.path='figs/')

## -----------------------------------------------------------------------------
# install.packages("sandwich")
library("sandwich")

## -----------------------------------------------------------------------------
bc.sampling = load.shp("./data", "bc_sampling")
bc.ssh = load.shp("./data", "bc_ssh")
bc.reporting = load.shp("./data", "bc_reporting")

## -----------------------------------------------------------------------------
bc.join = ssh.data(bc.sampling, bc.ssh, "Class")
bc.join

## -----------------------------------------------------------------------------
ssh.test(bc.join, "Incidence", "Class", test="factor")

## -----------------------------------------------------------------------------
bc.sw = sandwich.model(bc.sampling, bc.ssh, bc.reporting, "Incidence")
bc.sw

## ----fig.align="center", fig.width=4, fig.height=3----------------------------
# mean
plot.mean(bc.sw)
# standard error
plot.se(bc.sw)

## -----------------------------------------------------------------------------
bc.sw.ci = sandwich.ci(bc.sw, level=.95)
bc.sw.ci

## ----fig.align="center", fig.width=8, fig.height=3----------------------------
plot.ci(bc.sw.ci)

## -----------------------------------------------------------------------------
bc.cv = sandwich.cv(bc.sampling, bc.ssh, bc.reporting, "Incidence", k=5)
bc.cv

