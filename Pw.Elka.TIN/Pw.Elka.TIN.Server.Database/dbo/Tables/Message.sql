CREATE TABLE [dbo].[Message] (
    [id_message] INT           IDENTITY (1, 1) NOT NULL,
    [id_client]  INT           NOT NULL,
    [title]      VARCHAR (50)  NOT NULL,
    [content]    VARCHAR (500) NOT NULL,
    CONSTRAINT [PK_Message] PRIMARY KEY CLUSTERED ([id_message] ASC),
    CONSTRAINT [FK_Message_Client] FOREIGN KEY ([id_client]) REFERENCES [dbo].[Client] ([id_client])
);

