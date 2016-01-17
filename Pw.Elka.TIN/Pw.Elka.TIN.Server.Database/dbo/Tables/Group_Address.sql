CREATE TABLE [dbo].[Group_Address] (
    [id_group]   INT NOT NULL,
    [id_address] INT NOT NULL,
    CONSTRAINT [PK_Group_Address] PRIMARY KEY CLUSTERED ([id_group] ASC, [id_address] ASC),
    CONSTRAINT [FK_Group_Address_Address] FOREIGN KEY ([id_address]) REFERENCES [dbo].[Address] ([id_address]) ON DELETE CASCADE,
    CONSTRAINT [FK_Group_Address_Group] FOREIGN KEY ([id_group]) REFERENCES [dbo].[Group] ([id_group]) ON DELETE CASCADE,
    CONSTRAINT [grupa_adres] UNIQUE NONCLUSTERED ([id_group] ASC, [id_address] ASC)
);





