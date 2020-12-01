um umunittests/div.um > gts/div.gt
./um umunittests/div.um > ones/div.1
diff ones/div.1 gts/div.gt

um umunittests/add.um > gts/add.gt
./um umunittests/add.um > ones/add.1
diff ones/add.1 gts/add.gt

um umunittests/initoutput.um > gts/initoutput.gt
./um umunittests/initoutput.um > ones/initoutput.1
diff ones/initoutput.1 gts/initoutput.gt

um umunittests/cmov.um > gts/cmov.gt
./um umunittests/cmov.um > ones/cmov.1
diff ones/cmov.1 gts/cmov.gt

um umunittests/loadv.um > gts/loadv.gt
./um umunittests/loadv.um > ones/loadv.1
diff ones/loadv.1 gts/loadv.gt


um umunittests/halt.um > gts/halt.gt
./um umunittests/halt.um > ones/halt.1
diff ones/halt.1 gts/halt.gt

um umunittests/input.um > gts/input.gt
./um umunittests/input.um > ones/input.1
diff ones/input.1 gts/input.gt

./um umunittests/loadp_difseg.um > ones/loadp_difseg.1
um umunittests/loadp_difseg.um > gts/loadp_difseg.gt
diff ones/loadp_difseg.1 gts/loadp_difseg.gt

./um umunittests/loadp_sameseg.um < /dev/null > ones/loadp_sameseg.1
um umunittests/loadp_sameseg.um > gts/loadp_sameseg.gt
diff ones/loadp_sameseg.1 gts/loadp_sameseg.gt

./um umunittests/map_unmap_stress.um > ones/map_unmap_stress.1
um umunittests/map_unmap_stress.um > gts/map_unmap_stress.gt
diff ones/map_unmap_stress.1 gts/map_unmap_stress.gt

./um umunittests/mapstress.um > ones/mapstress.1
um umunittests/mapstress.um > gts/mapstress.gt
diff ones/mapstress.1 gts/mapstress.gt

./um umunittests/mult.um > ones/mult.1
um umunittests/mult.um > gts/mult.gt
diff ones/mult.1 gts/mult.gt

./um umunittests/nand.um > ones/nand.1
um umunittests/nand.um > gts/nand.gt
diff ones/nand.1 gts/nand.gt

./um umunittests/output.um > ones/output.1
um umunittests/output.um > gts/output.gt
diff ones/output.1 gts/output.gt

./um umunittests/sload.um > ones/sload.1
um umunittests/sload.um > gts/sload.gt
diff ones/sload.1 gts/sload.gt

./um umunittests/sstore.um > ones/sstore.1
um umunittests/sstore.um > gts/sstore.gt
diff ones/sstore.1 gts/sstore.gt

