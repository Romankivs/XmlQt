<?xml version="1.0" encoding="UTF-8" ?>

<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html"
                indent="yes"/>
    <xsl:template match="FacultyNetworkInformationServices">
        <html>
            <body>
                <table border="1">
                    <tr>
                        <th>Name</th>
                        <th>Annotation</th>
                        <th>Type</th>
                        <th>Version</th>
                        <th>Author</th>
                        <th>TermsAndConditionsOfUse</th>
                        <th>InformationWhenRegisteringUser</th>
                    </tr>
                    <xsl:for-each select="//Service">
                        <tr>
                            <td>
                                <xsl:value-of select="@Name"/>
                            </td>
                            <td>
                                <xsl:value-of select="@Annotation"/>
                            </td>
                            <td>
                                <xsl:value-of select="@Type"/>
                            </td>
                            <td>
                                <xsl:value-of select="@Version"/>
                            </td>
                            <td>
                                <xsl:value-of select="@Author"/>
                            </td>
                            <td>
                                <xsl:value-of select="@TermsAndConditionsOfUse"/>
                            </td>
                            <td>
                                <xsl:value-of select="@InformationWhenRegisteringUser"/>
                            </td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>
