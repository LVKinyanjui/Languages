package main

import (
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
)

func main() {
	InitDatabase()
	defer DB.Close()

	router := gin.Default()
	router.LoadHTMLGlob("templates/*")

	router.GET("/", func(c *gin.Context) {
		todos, err := ReadToDoList()
		if err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
			return
		}
		c.HTML(http.StatusOK, "index.html", gin.H{
			"todos": todos,
		})

		router.POST("/todos", func(c *gin.Context) {
			title := c.PostForm("title")
			status := c.PostForm("status")
			id, err := CreateToDo(title, status)
			if err != nil {
				c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
				return
			}
			c.HTML(http.StatusOK, "task.html", gin.H{
				"title":  title,
				"status": status,
				"id":     id,
			})
		})

		router.DELETE("/todos/:id", func(c *gin.Context) {
			param := c.Param("id")
			id, err := strconv.ParseInt(param, 10, 64)
			if err != nil {
				c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid ID"})
				return
			}
			err = DeleteToDo(id)
			if err != nil {
				c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
				return
			}
			c.JSON(http.StatusOK, gin.H{"message": "ToDo deleted successfully"})
		})

	})

	router.Run("localhost:8000")
}
