CREATE TABLE [dbo].[Address] (
    [id_address]     INT          IDENTITY (1, 1) NOT NULL,
    [addressee_name] VARCHAR (50) NOT NULL,
    [address_name]   VARCHAR (50) NOT NULL,
    [id_client]      INT          NOT NULL,
    CONSTRAINT [PK_Address_1] PRIMARY KEY CLUSTERED ([id_address] ASC)
);



