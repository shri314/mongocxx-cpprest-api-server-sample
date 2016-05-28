db.Vehicle.drop();
db.createCollection("Vehicle");
db.Vehicle.insert( [
                      { _id:  1, Vehicle_Registration: "MHCA_01", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_01", Vehicle_Owner: "TheBorg_01" },
                      { _id:  2, Vehicle_Registration: "MHCA_02", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_01", Vehicle_Owner: "TheBorg_01" },
                      { _id:  3, Vehicle_Registration: "MHCA_03", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_01", Vehicle_Owner: "TheBorg_02" },
                      { _id:  4, Vehicle_Registration: "MHCA_04", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_01", Vehicle_Owner: "TheBorg_02" },
                      { _id:  5, Vehicle_Registration: "MHCA_05", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_01", Vehicle_Owner: "TheBorg_03" },
                      { _id:  6, Vehicle_Registration: "MHCA_06", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_01", Vehicle_Owner: "TheBorg_03" },
                      { _id:  7, Vehicle_Registration: "MHCA_07", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_01", Vehicle_Owner: "TheBorg_04" },
                      { _id:  8, Vehicle_Registration: "MHCA_08", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_01", Vehicle_Owner: "TheBorg_04" },
                      { _id:  9, Vehicle_Registration: "MHCA_09", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_02", Vehicle_Owner: "TheBorg_05" },
                      { _id: 10, Vehicle_Registration: "MHCA_10", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_02", Vehicle_Owner: "TheBorg_05" },
                      { _id: 11, Vehicle_Registration: "MHCA_11", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_02", Vehicle_Owner: "TheBorg_06" },
                      { _id: 12, Vehicle_Registration: "MHCA_12", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_02", Vehicle_Owner: "TheBorg_06" },
                      { _id: 13, Vehicle_Registration: "MHCA_13", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_02", Vehicle_Owner: "TheBorg_07" },
                      { _id: 14, Vehicle_Registration: "MHCA_14", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_02", Vehicle_Owner: "TheBorg_07" },
                      { _id: 15, Vehicle_Registration: "MHCA_15", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_02", Vehicle_Owner: "TheBorg_08" },
                      { _id: 16, Vehicle_Registration: "MHCA_16", Vehicle_Make: "Chevy_01", Vehicle_Model: "Model_02", Vehicle_Owner: "TheBorg_08" },

                      { _id: 17, Vehicle_Registration: "MHCA_17", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_03", Vehicle_Owner: "TheBorg_09" },
                      { _id: 18, Vehicle_Registration: "MHCA_18", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_03", Vehicle_Owner: "TheBorg_09" },
                      { _id: 19, Vehicle_Registration: "MHCA_19", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_03", Vehicle_Owner: "TheBorg_10" },
                      { _id: 20, Vehicle_Registration: "MHCA_20", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_03", Vehicle_Owner: "TheBorg_10" },
                      { _id: 21, Vehicle_Registration: "MHCA_21", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_03", Vehicle_Owner: "TheBorg_11" },
                      { _id: 22, Vehicle_Registration: "MHCA_22", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_03", Vehicle_Owner: "TheBorg_11" },
                      { _id: 23, Vehicle_Registration: "MHCA_23", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_03", Vehicle_Owner: "TheBorg_12" },
                      { _id: 24, Vehicle_Registration: "MHCA_24", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_03", Vehicle_Owner: "TheBorg_12" },
                      { _id: 25, Vehicle_Registration: "MHCA_25", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_04", Vehicle_Owner: "TheBorg_13" },
                      { _id: 26, Vehicle_Registration: "MHCA_26", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_04", Vehicle_Owner: "TheBorg_13" },
                      { _id: 27, Vehicle_Registration: "MHCA_27", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_04", Vehicle_Owner: "TheBorg_14" },
                      { _id: 28, Vehicle_Registration: "MHCA_28", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_04", Vehicle_Owner: "TheBorg_14" },
                      { _id: 29, Vehicle_Registration: "MHCA_29", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_04", Vehicle_Owner: "TheBorg_15" },
                      { _id: 30, Vehicle_Registration: "MHCA_30", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_04", Vehicle_Owner: "TheBorg_15" },
                      { _id: 31, Vehicle_Registration: "MHCA_31", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_04", Vehicle_Owner: "TheBorg_16" },
                      { _id: 32, Vehicle_Registration: "MHCA_32", Vehicle_Make: "Chevy_02", Vehicle_Model: "Model_04", Vehicle_Owner: "TheBorg_16" },
                  ]
               );

db.VehicleQueries.drop();
db.createCollection("VehicleQueries");
