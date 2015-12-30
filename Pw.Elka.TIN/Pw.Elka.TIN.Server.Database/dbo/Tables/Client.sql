CREATE TABLE [dbo].[Client] (
    [id_client]     INT          IDENTITY (1, 1) NOT NULL,
    [login]         VARCHAR (50) NOT NULL,
    [password_hash] VARCHAR (50) NOT NULL,
    [blocked]       BIT          NOT NULL,
    CONSTRAINT [PK_Client] PRIMARY KEY CLUSTERED ([id_client] ASC)
);

