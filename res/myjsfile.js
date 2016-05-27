db.Vehicle.drop();
db.createCollection("Vehicle");
db.Vehicle.insert( [
                      { _id: 1, Vehicle_Registration: "MHCA0001", Vehicle_Make: "Chevy1", Vehicle_Model: "Model1", Vehicle_Owner: "Parag Shah1" },
                      { _id: 2, Vehicle_Registration: "MHCA0002", Vehicle_Make: "Chevy1", Vehicle_Model: "Model2", Vehicle_Owner: "Parag Shah2" },
                      { _id: 3, Vehicle_Registration: "MHCA0003", Vehicle_Make: "Chevy1", Vehicle_Model: "Model3", Vehicle_Owner: "Parag Shah3" },
                      { _id: 4, Vehicle_Registration: "MHCA0004", Vehicle_Make: "Chevy1", Vehicle_Model: "Model4", Vehicle_Owner: "Parag Shah4" },
                      { _id: 5, Vehicle_Registration: "MHCA0005", Vehicle_Make: "Chevy1", Vehicle_Model: "Model5", Vehicle_Owner: "Parag Shah5" },
                      { _id: 6, Vehicle_Registration: "MHCA0006", Vehicle_Make: "Chevy1", Vehicle_Model: "Model6", Vehicle_Owner: "Parag Shah6" },
                      { _id: 7, Vehicle_Registration: "MHCA0007", Vehicle_Make: "Chevy1", Vehicle_Model: "Model7", Vehicle_Owner: "Parag Shah7" },
                      { _id: 8, Vehicle_Registration: "MHCA0010", Vehicle_Make: "Chevy1", Vehicle_Model: "Model8", Vehicle_Owner: "Parag Shah8" },
                      { _id: 9, Vehicle_Registration: "MHCA0011", Vehicle_Make: "Chevy1", Vehicle_Model: "Model9", Vehicle_Owner: "Parag Shah9" },
                      { _id: 10, Vehicle_Registration: "MHCA0012", Vehicle_Make: "Chevy2", Vehicle_Model: "Model10", Vehicle_Owner: "Parag Shah10" },
                      { _id: 11, Vehicle_Registration: "MHCA0013", Vehicle_Make: "Chevy2", Vehicle_Model: "Model11", Vehicle_Owner: "Parag Shah11" },
                      { _id: 12, Vehicle_Registration: "MHCA0014", Vehicle_Make: "Chevy2", Vehicle_Model: "Model12", Vehicle_Owner: "Parag Shah12" },
                      { _id: 13, Vehicle_Registration: "MHCA0015", Vehicle_Make: "Chevy2", Vehicle_Model: "Model13", Vehicle_Owner: "Parag Shah13" },
                      { _id: 14, Vehicle_Registration: "MHCA0016", Vehicle_Make: "Chevy2", Vehicle_Model: "Model14", Vehicle_Owner: "Parag Shah14" },
                      { _id: 15, Vehicle_Registration: "MHCA0017", Vehicle_Make: "Chevy2", Vehicle_Model: "Model15", Vehicle_Owner: "Parag Shah15" },
                      { _id: 16, Vehicle_Registration: "MHCA0020", Vehicle_Make: "Chevy2", Vehicle_Model: "Model16", Vehicle_Owner: "Parag Shah16" },
                      { _id: 17, Vehicle_Registration: "MHCA0021", Vehicle_Make: "Chevy2", Vehicle_Model: "Model17", Vehicle_Owner: "Parag Shah17" },
                      { _id: 18, Vehicle_Registration: "MHCA0022", Vehicle_Make: "Chevy2", Vehicle_Model: "Model18", Vehicle_Owner: "Parag Shah18" },
                      { _id: 19, Vehicle_Registration: "MHCA0023", Vehicle_Make: "Chevy2", Vehicle_Model: "Model19", Vehicle_Owner: "Parag Shah19" },
                      { _id: 20, Vehicle_Registration: "MHCA0024", Vehicle_Make: "Chevy2", Vehicle_Model: "Model20", Vehicle_Owner: "Parag Shah20" },
                      { _id: 21, Vehicle_Registration: "MHCA0025", Vehicle_Make: "Chevy3", Vehicle_Model: "Model21", Vehicle_Owner: "Parag Shah21" },
                      { _id: 22, Vehicle_Registration: "MHCA0026", Vehicle_Make: "Chevy3", Vehicle_Model: "Model22", Vehicle_Owner: "Parag Shah22" },
                      { _id: 23, Vehicle_Registration: "MHCA0027", Vehicle_Make: "Chevy3", Vehicle_Model: "Model23", Vehicle_Owner: "Parag Shah23" },
                      { _id: 24, Vehicle_Registration: "MHCA0030", Vehicle_Make: "Chevy3", Vehicle_Model: "Model24", Vehicle_Owner: "Parag Shah24" },
                      { _id: 25, Vehicle_Registration: "MHCA0031", Vehicle_Make: "Chevy3", Vehicle_Model: "Model25", Vehicle_Owner: "Parag Shah25" },
                      { _id: 26, Vehicle_Registration: "MHCA0032", Vehicle_Make: "Chevy4", Vehicle_Model: "Model26", Vehicle_Owner: "Parag Shah26" },
                      { _id: 27, Vehicle_Registration: "MHCA0033", Vehicle_Make: "Chevy4", Vehicle_Model: "Model27", Vehicle_Owner: "Parag Shah27" },
                      { _id: 28, Vehicle_Registration: "MHCA0034", Vehicle_Make: "Chevy4", Vehicle_Model: "Model28", Vehicle_Owner: "Parag Shah28" },
                      { _id: 29, Vehicle_Registration: "MHCA0035", Vehicle_Make: "Chevy4", Vehicle_Model: "Model29", Vehicle_Owner: "Parag Shah29" },
                      { _id: 30, Vehicle_Registration: "MHCA0036", Vehicle_Make: "Chevy4", Vehicle_Model: "Model30", Vehicle_Owner: "Parag Shah30" },
                      { _id: 31, Vehicle_Registration: "MHCA0037", Vehicle_Make: "Chevy4", Vehicle_Model: "Model31", Vehicle_Owner: "Parag Shah31" },
                  ]
               );

db.VehicleQueries.drop();
db.createCollection("VehicleQueries");
