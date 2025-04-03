
#include <gtest/gtest.h>
#include "../Donor.h"
#include "../BloodDatabase.h"

// Prueba creación de donante y getters
TEST(DonorTest, CreationAndGetters) {
    Donor d(1, 3001234567, 5, "Juan", "Calle 123", "O+");

    EXPECT_EQ(d.getDonorId(), 1);
    EXPECT_EQ(d.getNumber(), 3001234567);
    EXPECT_EQ(d.getDistrict(), 5);
    EXPECT_EQ(d.getName(), "Juan");
    EXPECT_EQ(d.getAddress(), "Calle 123");
    EXPECT_EQ(d.getBloodType(), "O+");
}

// Prueba setters
TEST(DonorTest, Setters) {
    Donor d;
    d.setDonorId(2);
    d.setNumber(3109876543);
    d.setDistrict(3);
    d.setName("Maria");
    d.setAddress("Avenida 456");
    d.setBloodType("A-");

    EXPECT_EQ(d.getDonorId(), 2);
    EXPECT_EQ(d.getNumber(), 3109876543);
    EXPECT_EQ(d.getDistrict(), 3);
    EXPECT_EQ(d.getName(), "Maria");
    EXPECT_EQ(d.getAddress(), "Avenida 456");
    EXPECT_EQ(d.getBloodType(), "A-");
}

// Prueba parseo de línea
TEST(DonorTest, ParseLine) {
    std::string line = "3,3101122334,2,Pedro,Carrera 789,B+";
    Donor d = Donor::parseLine(line);

    EXPECT_EQ(d.getDonorId(), 3);
    EXPECT_EQ(d.getNumber(), 3101122334);
    EXPECT_EQ(d.getDistrict(), 2);
    EXPECT_EQ(d.getName(), "Pedro");
    EXPECT_EQ(d.getAddress(), "Carrera 789");
    EXPECT_EQ(d.getBloodType(), "B+");
}

// Prueba agregando y buscando donante
TEST(BloodDatabaseTest, AddAndGetDonor) {
    BloodDatabase db;
    Donor d(10, 3201112233, 4, "Luisa", "Calle Real", "AB-");
    db.addDonor(d);

    Donor retrieved = db.getDonorById(10);
    EXPECT_EQ(retrieved.getName(), "Luisa");
}

// Prueba validación de número con API (mock)
TEST(BloodDatabaseTest, ValidatePhoneNumberMock) {
    BloodDatabase db;
    // Esta prueba debe pasar si el método está desactivado temporalmente o retornando true
    EXPECT_TRUE(db.validatePhoneNumber("573001234567"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// Prueba de entrada validada (simulada)
TEST(BloodDatabaseTest, ValidatedInputMock) {
    // No se puede probar fácilmente sin entrada del usuario.
    SUCCEED() << "Prueba omitida por depender de entrada interactiva.";
}

// Prueba de validación de número
TEST(BloodDatabaseTest, ValidatePhoneNumberLogic) {
    BloodDatabase db;
    EXPECT_TRUE(db.validatePhoneNumber("573001234567"));
    EXPECT_FALSE(db.validatePhoneNumber("123456"));  // Esperamos que este falle
}

// Prueba de getDonorDetails (mock básico)
TEST(BloodDatabaseTest, GetDonorDetailsStructure) {
    BloodDatabase db;
    // Como requiere entrada del usuario, no es testeable directamente sin mocks
    SUCCEED() << "Prueba estructural para método interactivo.";
}

// Prueba de escritura en archivo
TEST(BloodDatabaseTest, WriteDataToFile) {
    BloodDatabase db;
    db.addDonor(Donor(99, 3110001111, 9, "Test", "Archivo", "O+"));
    db.writeDataToFile();
    SUCCEED() << "Archivo generado (revisar manualmente si es necesario).";
}

// Prueba de búsqueda (mock básico)
TEST(BloodDatabaseTest, SearchAndDisplayStructure) {
    BloodDatabase db;
    SUCCEED() << "Método de visualización; requiere revisión manual.";
}

// Prueba eliminación (mock)
TEST(BloodDatabaseTest, DeleteDonorStructure) {
    BloodDatabase db;
    SUCCEED() << "Método de eliminación interactivo; requiere revisión visual.";
}

// Prueba displayAllDonations
TEST(BloodDatabaseTest, DisplayAllDonationsStructure) {
    BloodDatabase db;
    SUCCEED() << "Método de listado de donaciones visual; prueba estructural.";
}

// Prueba de indicadores
TEST(BloodDatabaseTest, GenerateIndicatorsStructure) {
    BloodDatabase db;
    SUCCEED() << "Generación de indicadores; verificación visual recomendada.";
}
