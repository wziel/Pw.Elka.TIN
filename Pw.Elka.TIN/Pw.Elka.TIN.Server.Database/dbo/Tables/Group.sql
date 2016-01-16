CREATE TABLE [dbo].[Group] (
    [id_group]  INT           IDENTITY (1, 1) NOT NULL,
    [id_client] INT           NOT NULL,
    [name]      VARCHAR (100) NOT NULL,
    CONSTRAINT [PK_Group] PRIMARY KEY CLUSTERED ([id_group] ASC),
    CONSTRAINT [FK_Group_Client] FOREIGN KEY ([id_client]) REFERENCES [dbo].[Client] ([id_client]),
    CONSTRAINT [grupa_klient] UNIQUE NONCLUSTERED ([id_client] ASC, [name] ASC)
);



